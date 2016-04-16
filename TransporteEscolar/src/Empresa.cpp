#include "Empresa.h"

// criar veiculo ==
using namespace std;

Empresa::Empresa(string nome, Morada endereco)
{
	this->nome = nome;
	this->endereco = endereco;
	mapa = new Mapa();

	mapa->setPontoInteresse(endereco);
}

string Empresa::getNome() const {return nome;}

Morada Empresa::getEndereco() const {return endereco;}

Mapa* Empresa::getMapa() const {return mapa;}

void Empresa::setNome(string nome) {this->nome = nome;}

void Empresa::setEndereco(Morada endereco) {this->endereco = endereco;}

bool Empresa::addTransporte(Veiculo * veiculo)
{
	for(unsigned int i = 0; i < transportes.size(); i++)
		if(veiculo == transportes[i])
			return false;
	veiculo->setPartida(endereco); // o veiculo parte da sede da empresa
	transportes.push_back(veiculo);
	return true;
}

/**
 * ao adicionar o cliente, adicionamos a sua morada como ponto de interesse
 */
bool Empresa::addCliente(Cliente * cliente)
{
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(*cliente == *clientes[i])
			return false;
	clientes.push_back(cliente);
	mapa->setPontoInteresse(cliente->getResidencia());

	return true;
}

bool Empresa::removeTransporte(Veiculo * veiculo)
{
	for(unsigned int i = 0; i < transportes.size(); i++)
		if(veiculo == transportes[i]){
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
			mapa->getPontoVertex(clientes[i]->getResidencia().getID())->setIsPI(0);
			delete(*(clientes.begin()+i));
			clientes.erase(clientes.begin() + i);
			return true;
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
				mapa->setPontoInteresse(clientes.at(j)->getEscola());
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
		vector<Morada> res = transportes.at(i)->makePath();
		displayMapa(mapa->shortestPath(res));
	}

}

void Empresa::displayClientes() const{
	for (size_t i = 0; i < clientes.size(); ++i) {
		cout << *clientes[i] << endl;
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

/**
 * FAZER
 */
void Empresa::displayMapa(vector<Morada> points){

	mapa->displayMapa(points);
	//temporario
	for(size_t i = 0; i < points.size(); i++)
		cout << points.at(i).getID() << endl;

}
