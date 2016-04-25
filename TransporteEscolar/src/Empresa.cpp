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
	isEscola = false;
	this->nome = nome;
	this->endereco = endereco;
	mapa = new Mapa();
}

string Empresa::getNome() const {return nome;}

Morada* Empresa::getEndereco() const {return endereco;}

void Empresa::setIsEscola(bool b){ isEscola =b; }

bool Empresa::getIsEscola() const{ return isEscola; }

vector<Morada *> Empresa::getEscolas() const{ return escolas; }

Mapa* Empresa::getMapa() const {return mapa;}

void Empresa::setNome(string nome) {this->nome = nome;}

void Empresa::setEndereco(Morada *endereco) {this->endereco = endereco;}

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

void Empresa::setClientesPI(int id){
	vector<Cliente *> mudar_cli;
	//Seleccionar os clientes com a residencia com o mesmo id
	for (size_t i = 0; i < clientes.size(); ++i) {
		if(clientes[i]->getResidencia()->getID() == id)
			mudar_cli.push_back(clientes[i]);
	}
	//ir buscar o ponto de recolha mais próximo a id
	vector<Morada> pontosRecolha = mapa->getInterestPoints();

	int indice1 = -1,indice2 = -1;
	//procurar o indice do ponto de recolha com id
	for (size_t i = 0; i < pontosRecolha.size(); ++i) {
		if(pontosRecolha[i].getID() == id)
			indice1 = i;
	}

	if(indice1 == -1){
		cout << "Indice Invalido" << endl;
		throw VoltarAtras();
	}
	indice2 = mapa->getMinDistBetweenPoints(indice1,pontosRecolha);

	if(indice1 == indice2 || indice2 == -1)
		throw PontoRecolhaInvalido(pontosRecolha[indice1]);

	//substituir clientes para o ponto de recolha de indice2 em pontosRecolha

	Morada *m = new Morada(getEndereco()->getX(),getEndereco()->getY(),pontosRecolha[indice2].getID());
	for (size_t i = 0; i < mudar_cli.size(); ++i) {
		mudar_cli[i]->setNovaResidencia(m);
	}
}

bool Empresa::addTransporte(Veiculo * veiculo)
{
	if(veiculo->getNumLugares() <= 0)
		return false;
	for(unsigned int i = 0; i < transportes.size(); i++){
		if((*veiculo) == (*transportes[i])){
			return false;
		}
	}
	transportes.push_back(veiculo);
	return true;
}

bool Empresa::addCliente(Cliente * cliente)
{
	Cliente::id--; //para o caso de dar throw
	//veiculos insuficientes2
	int lugares = 0;
	for (size_t i = 0; i < transportes.size(); ++i) {
		lugares += transportes[i]->getNumLugares();
	}
	//Residencia nao e um ponto de interesse
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
			return false;
		}
	//residencia = escola(Empresa->escolas)
	for (size_t j = 0; j < escolas.size(); ++j) {
		if(*cliente->getResidencia() == *escolas[j])
			return false;
	}
	clientes.push_back(cliente);
	addEscola(cliente->getEscola());
	Cliente::id++;
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
			for (size_t var = 0; var < transportes.size(); ++ var) {
				transportes[var]->sairCliente(cliente);
			}
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

bool Empresa::displayTrajetosIda(string matricula){

	for (size_t i = 0; i < transportes.size(); ++i) {
		if(transportes[i]->getMatricula() == matricula){
			vector<Morada> res = transportes.at(i)->getCaminho();
			vector<Morada> path = mapa->makePath(res);
			mapa->displayMapa(path);
			return true;
		}
	}
	return false;
}

bool Empresa::displayTrajetosVolta(string matricula){

	for(size_t i = 0; i < transportes.size(); i++){

		if(transportes.at(i)->getMatricula() == matricula){

			vector<Morada> res = transportes.at(i)->getCaminho();
			vector<Morada> invert;

			for(size_t j = res.size()-1; j > 0; j--)
				invert.push_back(res.at(j));
			invert.push_back(res.at(0));

			vector<Morada> path = mapa->makePath(invert);
			mapa->displayMapa(path);
			return true;
		}
	}
	return false;
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
	vector<Morada> tmp;

	for (size_t i = 0; i < getEscolas().size(); ++i) {
		tmp.push_back(*getEscolas()[i]);
		cout << tmp[i] << endl;
	}
	mapa->displayMapa(tmp);
}

void Empresa::displayPontosRecolha() const{
	vector<Morada> pi = mapa->getInterestPoints();
	for (size_t i = 0; i < pi.size(); ++i) {
		cout << pi[i] << " n Clientes: " << getClientesPontoRecolha(&pi[i]).size() << endl;
	}
	mapa->displayMapa(pi);
}


void Empresa::distribuiCliVeiculos(){

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

		transportes.at(j)->pushCaminho(*endereco);	//o primeiro ponto a colocar no trajeto é o endereco da empresa

		if(end)
			break;

		int p = 0; // comeca sempre no ponto 0 (indice do vetor pi)
		int min = 0; // ponto mais proximo (indice do vetor pi)
		vector<Morada > dest; //escolas destino

		//marca as escolas como não processadas
		for(size_t i = 0; i < escolas.size(); i++)
			mapa->setPontoProcessado(*escolas.at(i), false);

		while(transportes.at(j)->lugaresLivres() != 0){
			// chamar o grafo para ver se deste ponto de interesse(k), qual o que está mais proximo.
			//Retorna o id do mais proximo.
			min = mapa->getMinDistBetweenPoints(p,pi);

			//se forem iguais chegamos ao fim de todos os pontos de interesse
			if(p == min){
				end = true;
				break;
			}

			transportes.at(j)->pushCaminho(pi.at(min)); 	//colocar  na lifo do veiculo este ponto

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

		//desobrir quantas escolas diferentes estão no veiculo
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
			min = mapa->getMinDistBetweenPoints(p,dest);
			mapa->setPontoProcessado(dest.at(min), true);
			transportes.at(j)->pushCaminho(dest.at(min));
			p = min;
		}
	}

}

void Empresa::initialization(){

}

void Empresa::guardarInfo() const{
	fstream file;
	if(isEscola)
		file.open("escolaInfo.txt");
	else
		file.open("empresaInfo.txt");

	if(file.fail()){
		cout << "Error at opening the file\n";
	}

	//empresa
	file << nome << " " << *endereco << endl;
	file << "=========================" << endl;
	//transportes
	for (size_t i = 0; i < transportes.size(); i++) {
		file << transportes[i]->getMatricula() << " " << transportes[i]->getNumLugares() << endl;
	}
	//pontos recolha
	file << "=========================" << endl;
	vector<Morada> recolha = mapa->getInterestPoints();
	for (size_t i = 0; i < recolha.size(); ++i) {
		file << recolha[i]<< endl;
	}
	file << "=========================" << endl;
	//clientes
	file << Cliente::id << endl;
	for (size_t i = 0; i < clientes.size(); ++i) {
		file << clientes[i]->getID() << " " <<clientes[i]->getNome()<< " " << *clientes[i]->getResidencia()<< " " << *clientes[i]->getEscola() << endl;
	}
	file.close();
}

void Empresa::carregarInfo(){
	fstream file;
	string tmp;
	stringstream linha;
	if(isEscola)
		file.open("escolaInfo.txt");
	else
		file.open("empresaInfo.txt");
	string nome;
	string matricula;
	int id,id2 ,coordx,coordy, nLugares,coordx2,coordy2,cliente_n;
	char lixo;
	string separador = "=========================";

	if(file.fail()){
		cout << "Error at opening the file\n";
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
			addTransporte(new Veiculo(matricula, nLugares));
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
			Cliente *c = new Cliente(nome,casa);
			if(isEscola)
				c->setNovaEscola(endereco);
			else
				c->setNovaEscola(escola);
			c->setID(cliente_n);
			addCliente(c);
		}
		Cliente::id = id_tmp;
	}

	file.close();
}
