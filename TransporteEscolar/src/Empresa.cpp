#include "Empresa.h"
#include <sstream>
#include <fstream>
#include <string.h>

// criar veiculo ==
using namespace std;

Empresa::Empresa(string nome, Morada *endereco)
{
	this->nome = nome;
	this->endereco = endereco;
	mapa = new Mapa();

	mapa->setPontoInteresse(*endereco);
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
	//residencia = escola
	if(cliente->getEscola()->getID() == cliente->getResidencia()->getID())
		return false;
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

/**
 * ainda não são consideradas formas eficientes de colocar os alunos
 * inicialmente todos os alunos vao para a mesma escola
 */
void Empresa::distribuiCliVeiculos(){

	size_t i = 0, j = 0;
	while(i != transportes.size()){
		while(j != clientes.size()){
			if(transportes.at(i)->lugaresLivres() != 0)
				transportes.at(i)->addCliente(clientes.at(j));
			else{ //ultimo lugar do veiculo
				transportes.at(i)->setDestino(clientes.at(j)->getEscola()); //TEMPORARIO
				mapa->setPontoInteresse(*clientes.at(j)->getEscola());
				break;
			}

			if(j == clientes.size()-1) //ultimo cliente
				transportes.at(i)->setDestino(clientes.at(j)->getEscola()); //TEMPORARIO
			j++;
		}
		i++;
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
			linha >> matricula >> nLugares >> nome;
			addTransporte(new Veiculo(nLugares,matricula));
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
			Morada *escola = new Morada(coordx2,coordy,id2);
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
