#include "Empresa.h"
#include <sstream>
#include <fstream>
#include <string.h>
#include "Excessoes.h"
#include <algorithm>

using namespace std;
/*
 * FUNÇÕES CARRREGAR E GUARDAR A ACEITAR GETLINES
 */

Empresa::Empresa(string nome, Morada *endereco)
{
	this->nome = nome;
	this->endereco = endereco;
	mapa = new Mapa();
}

string Empresa::getNome() const {return nome;}

Morada* Empresa::getEndereco() const {return endereco;}

vector<Morada *> Empresa::getEscolas() const{
	return escolas;
}

Mapa* Empresa::getMapa() const {return mapa;}

void Empresa::setNome(string nome) {this->nome = nome;}

void Empresa::setEndereco(Morada *endereco) {this->endereco = endereco;}

bool Empresa::addTransporte(Veiculo * veiculo)
{
	if(veiculo->getNumLugares() <= 0)
		return false;
	for(unsigned int i = 0; i < transportes.size(); i++){
		if((*veiculo) == (*transportes[i])){
			return false;
		}
	}
	veiculo->setPartida(endereco); // o veiculo parte da sede da empresa
	transportes.push_back(veiculo);
	return true;
}

bool Empresa::addCliente(Cliente * cliente)
{
	//veiculos insuficientes2
	int lugares = 0;
	for (int i = 0; i < transportes.size(); ++i) {
		lugares += transportes[i]->getNumLugares();
	}
	//Residencia nao e um ponto de interesse (crasha lool)
	if(mapa->isPontoInteresse(*cliente->getResidencia()) == false)
		throw PontoRecolhaInvalido(*cliente->getResidencia());
	if(lugares < clientes.size())
		throw VeiculosInsuficientes();
	//residencia = escola
	if(cliente->getEscola()->getID() == cliente->getResidencia()->getID())
		throw ResidenciaInvalida(*cliente->getResidencia());
	//cliente já existe, id = ou residencia =
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(*cliente == *clientes[i]){
			Cliente::id--;
			return false;
		}
	//residencia = escola(Empresa->escolas)
	for (int j = 0; j < escolas.size(); ++j) {
		if(*cliente->getResidencia() == *escolas[j])
			return false;
	}
	clientes.push_back(cliente);
	addEscola(cliente->getEscola());
	return true;
}

bool Empresa::addEscola(Morada *e){
	vector<Morada *>::iterator itb = escolas.begin();
	vector<Morada *>::iterator itf = escolas.end();

	while(itb != itf){
		if(*(*itb) == *e)
			return false;
		itb++;
	}
	escolas.push_back(e);
	return true;
}

bool Empresa::removeTransporte(Veiculo * veiculo)
{
	Veiculo *v;
	for(unsigned int i = 0; i < transportes.size(); i++)
		if(*veiculo == *transportes[i]){
			v = transportes[i];
			transportes.erase(transportes.begin() + i);
			delete(v);
			return true;
		}
	return false;
}

bool Empresa::removeCliente(Cliente * cliente)
{
	Cliente *c;
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(cliente == clientes[i]){
			for (int var = 0; var < transportes.size(); ++ var) {
				transportes[i]->sairCliente(clientes[i]);
			}
			mapa->getPontoVertex(clientes[i]->getResidencia()->getID())->setIsPI(0);
			removerEscola(cliente->getEscola());
			c = clientes[i];
			clientes.erase(clientes.begin() + i);
			delete(c);
			return true;
		}
	return false;
}

bool Empresa::removeCliente(int id){
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(id == clientes[i]->getID()){
			return removeCliente(clientes[i]);
		}
	return false;
}

//VER DEPOIS NÃO FUNCIONA
bool Empresa::removerEscola(Morada *e){
	vector<Cliente *>::iterator itb = clientes.begin();
	vector<Cliente *>::iterator itf = clientes.end();
	vector<Morada *>::iterator itbm = escolas.begin();
	vector<Morada *>::iterator itfm = escolas.end();
	int n = 0;

	//ver se existe outro cliente com a mesma escola
	while(itb != itf){
		if(*(*itb)->getEscola() == *e)
			n++;
		itb++;
	}
	if(n > 1 || n==0)
		return false;
	//ver se a escola pertence as escolas
	while(itbm != itfm){
		if(*(*itbm) == *e){
			delete(*itbm);
			escolas.erase(itbm);
			return true;
		}
		itbm++;
	}
	return false;
}

bool compararVeiculos(Veiculo *v1 , Veiculo *v2){
	if(v1->getNumLugares() < v2->getNumLugares())
		return true;
	else
		return false;
}

void Empresa::distribuiCliVeiculos(){

	mapa->makefloydWarshallShortestPath(); //crias as tabelas do path e dist entre todos os pontos

	bool end = false;
	vector<Morada > pi; //vetor com todos os pontos de interesse
	vector<Morada > temp = mapa->getInterestPoints();

	pi.push_back(*endereco); //comeca na morada da empresa
	mapa->setPontoProcessado(*endereco,true); //o primeiro ponto é processado
	for(size_t i = 0; i < temp.size(); i++)
		pi.push_back(temp.at(i));

	//marca todos os pi com 0 criancas como processados (o primeiro não conta)
	for(size_t i = 1; i < pi.size(); i++){
		vector<Cliente *> clientes = getClientesPontoRecolha(&pi.at(i));
		if(clientes.size() != 0)//vê se o nesse ponto existem criancas
			mapa->setPontoProcessado(pi.at(i), false);
		else
			mapa->setPontoProcessado(pi.at(i), true);
	}

	for(size_t j = 0; j < transportes.size(); j++){

		if(end)
			break;

		int p = 0; // comeca sempre no ponto 0
		int min = 0; // ponto mais proximo
		vector<Morada > dest; //escolas destino
		vector<Morada > path; //vetor com o caminho

		path.push_back(*endereco); // o primeiro ponto é a empresa

		//marca as escolas como não processadas
		for(size_t i = 0; i < escolas.size(); i++)
			mapa->setPontoProcessado(*escolas.at(i), false);

		while(transportes.at(j)->lugaresLivres() != 0){

			// chamar o grafo para ver se deste ponto de interesse(k), qual o que está mais proximo.
			//Retorna o id do mais proximo.
			min = mapa->getMinDistBetweenPoints(p,pi,path);

			//se forem iguais chegamos ao fim de todos os pontos de interesse
			if(p == min){
				end = true;
				break;
			}

			// adiciona as criancas desse destino ao vetor de clientes da carrinha em causa.
			size_t n = 0;
			vector<Cliente *> clientes = getClientesPontoRecolha(&pi.at(min)) ; // clientes por ponto de interesse
			while(transportes.at(j)->lugaresLivres() != 0 && n != clientes.size()){
				transportes.at(j)->addCliente(clientes.at(n));
				pi.at(min).decNumCriancas();
				mapa->setPontoProcessado(*clientes.at(n)->getEscola(), true); //escola marcada como processada -> é destino
				n++;
			}

			//se todas as criancas entraram no autocarro, esse ponto é marcado como processado
			if(pi.at(min).getNumCriancas() == 0)
				mapa->setPontoProcessado(pi.at(min), true);

			p = min;
		}

		//descobrir quantas escolas diferentes estão no veiculo
		dest.push_back(pi.at(p)); //ultimo ponto
		for(size_t k = 0; k < escolas.size(); k++)
			if(mapa->getPontoProcessado(*escolas.at(k)) == true) //se foram processadas é porque existem alunos no veiculo que as frequentam
				dest.push_back(*escolas.at(k));


		//remarca as escolas como não processadas
		for(size_t i = 0; i < escolas.size(); i++)
			mapa->setPontoProcessado(*escolas.at(i), false);


		//procurar do ultimo ponto a escola mais proxima
		p = 0;
		for(size_t k = 1; k < dest.size(); k++){
			min = mapa->getMinDistBetweenPoints(p,dest,path);
			p = min;
		}

		//marcar como destino a escola onde chegou
		transportes.at(j)->setDestino(&dest.at(p));

		//MUDAR ISTO !!!!
		mapa->displayMapa(path);
	}

}

/**
 * funcao que faz display dos mapas dos veiculos ou display de um só mapa com todos os veiculos
 * (decidir depois)
 */
void Empresa::enviaVeiculos(){

	for(size_t i = 0; i < transportes.size(); i++){
		vector<Morada> res = transportes.at(i)->makePath(); //pontos de interesse
		res = mapa->shortestPath(res); //menor caminho que passa nesses pontos de interesse
		mapa->displayMapa(res);
	}

}

void Empresa::displayClientes() const{
	for (size_t i = 0; i < clientes.size(); ++i) {
		cout << *clientes[i] << endl;
	}
}

void Empresa::displayVeiculos() const{
	for (size_t i = 0; i < transportes.size(); ++i) {
		cout << *transportes[i] << endl;
	}
}

void Empresa::displayEscolas() const{
	for (size_t i = 0; i < escolas.size(); ++i) {
		cout << *escolas[i] << endl;
	}
}

void Empresa::displayPontosRecolha() const{
	vector<Morada> pi = mapa->getInterestPoints();
	for (size_t i = 0; i < pi.size(); ++i) {
		cout << pi[i] << " n Clientes: " << getClientesPontoRecolha(&pi[i]).size() << endl;
	}
}

void Empresa::guardarInfo() const{
	fstream file;
	file.open("info.txt");

	if(file.fail()){
		cout << "Error at opening info.txt\n";
	}

	//empresa
	file << nome << " " << *endereco << endl;
	file << "=========================" << endl;
	//transportes
	for (int i = 0; i < transportes.size(); i++) {
		file << transportes[i]->getMatricula() << " " << transportes[i]->getNumLugares() << endl;
	}
	//pontos recolha
	file << "=========================" << endl;
	vector<Morada> recolha = mapa->getInterestPoints();
	for (int i = 0; i < recolha.size(); ++i) {
		file << recolha[i]<< endl;
	}
	file << "=========================" << endl;
	//clientes
	file << Cliente::id << endl;
	for (int i = 0; i < clientes.size(); ++i) {
		file << clientes[i]->getID() << " " <<clientes[i]->getNome()<< " " << *clientes[i]->getResidencia()<< " " << *clientes[i]->getEscola() << endl;
	}
	file.close();
}

void Empresa::carregarInfo(){
	fstream file;
	string tmp;
	stringstream linha;
	file.open("info.txt");
	string nome;
	string matricula;
	int id,id2 ,coordx,coordy, nLugares, coordx2,coordy2,cliente_n;
	char lixo;
	string separador = "=========================";

	if(file.fail()){
		cout << "Error at opening info.txt\n";
	}

	if(!file.eof()){
		//empresa
		getline(file,tmp);
		linha << tmp;
		linha >> nome >> id >> lixo >> coordx >> lixo >> coordy >> lixo;
		setNome(nome);
		getEndereco()->setID(id);
		getEndereco()->setX(coordx);
		getEndereco()->setY(coordy);
		linha.clear();
		getline(file,tmp); // "========================="

		//transportes
		getline(file,tmp);
		while(tmp != separador){
			linha << tmp;
			linha >> matricula >> nLugares;
			addTransporte(new Veiculo(matricula));
			linha.clear();
			getline(file,tmp);
		}

		//pontos de recolha
		linha.clear();
		getline(file,tmp);
		while(tmp != separador){
			linha << tmp;
			linha >> id >> lixo >> coordx >> lixo >> coordy >> lixo;
			Morada ponto(coordx,coordy,id);
			mapa->setPontoInteresse(ponto,true);
			linha.clear();
			getline(file,tmp);
		}

		//clientes
		int id_tmp;
		getline(file,tmp);//IDDD
		linha << tmp;
		linha >> id_tmp;
		while(!file.eof()){
			linha.clear();
			getline(file,tmp);
			linha << tmp;
			linha >> cliente_n >> nome >> id >> lixo >> coordx >> lixo >> coordy >> lixo >> id2 >> lixo >> coordx2 >> lixo >> coordy2 >> lixo;
			Morada *casa = new Morada(coordx,coordy,id);
			casa->incNumCriancas();
			Morada *escola = new Morada(coordx2,coordy2,id2);
			Cliente *c = new Cliente(nome,casa,escola);
			c->setID(cliente_n);
			addCliente(c);
		}

		Cliente::id = id_tmp;

	}
	file.close();
}

vector<Cliente *> Empresa::getClientesEscola(Morada *escola) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
	vector<Cliente *>::const_iterator itf = clientes.end();
	vector<Cliente *> res;
	while(itb != itf){
		if(*(*itb)->getEscola() == *escola)
			res.push_back(*itb);
		itb++;
	}
	return res;
}

vector<Cliente *> Empresa::getClientesPontoRecolha(Morada * ponto) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
	vector<Cliente *>::const_iterator itf = clientes.end();
	vector<Cliente *> c;
	if(mapa->isPontoInteresse(*ponto) == false)
		throw PontoRecolhaInvalido(*ponto);
	while(itb != itf){
		if(*(*itb)->getResidencia() == *ponto)
			c.push_back(*itb);
		itb++;
	}
	return c;
}

