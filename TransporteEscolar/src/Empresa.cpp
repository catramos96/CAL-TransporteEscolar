#include "Empresa.h"

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
	if(cliente->getEscola()->getID() == cliente->getResidencia()->getID())
		return false;
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(*cliente == *clientes[i])
			return false;
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
	for(unsigned int i = 0; i < transportes.size(); i++)
		if(*veiculo == *transportes[i]){
			delete(*(transportes.begin()+i));
			transportes.erase(transportes.begin() + i);
			return true;
		}
	return false;
}

bool Empresa::removeCliente(Cliente * cliente)
{
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(cliente == clientes[i]){
			cout << "encontrei 1" << endl;
			for (int var = 0; var < transportes.size(); ++ var) {
				transportes[i]->sairCliente(clientes[i]);
			}
			mapa->getPontoVertex(clientes[i]->getResidencia()->getID())->setIsPI(0);
			removerEscola(cliente->getEscola());
			delete(*(clientes.begin()+i));
			clientes.erase(clientes.begin() + i);
			return true;
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

bool Empresa::removeCliente(int id){
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(id == clientes[i]->getID()){
			for (size_t var = 0; var < transportes.size(); ++ var) {
				transportes[i]->sairCliente(clientes[i]);
			}
			//mapa->getPontoVertex(clientes[i]->getResidencia().getID())->setIsPI(false);
			clientes.erase(clientes.begin() + i);
			return true;
		}
	return false;
}
