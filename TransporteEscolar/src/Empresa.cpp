#include "Empresa.h"

// criar veiculo ==
using namespace std;

Empresa::Empresa(string nome, Morada endereco)
{
	this->nome = nome;
	this->endereco = endereco;
}

string Empresa::getNome() const {return nome;}

Morada Empresa::getEndereco() const {return endereco;}

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

bool Empresa::addCliente(Cliente * cliente)
{
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(*cliente == *clientes[i])
			return false;
	clientes.push_back(cliente);
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
			for (int var = 0; var < transportes.size(); ++ var) {
				transportes[i]->sairCliente(clientes[i]);
			}
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

	int i = 0, j = 0;
	while(i != transportes.size()){
		while(j != clientes.size()){
			if(transportes.at(i)->lugaresLivres() != 0)
				transportes.at(i)->addCliente(clientes.at(j));
			else{ //ultimo lugar do veiculo
				transportes.at(i)->setDestino(clientes.at(j)->getEscola()); //TEMPORARIO
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

	for(int i = 0; i < transportes.size(); i++){
		transportes.at(i)->makeMapa();
		transportes.at(i)->displayMapa();
	}
}

void Empresa::displayClientes() const{
	for (int i = 0; i < clientes.size(); ++i) {
		cout << *clientes[i] << endl;
	}
}

bool Empresa::removeCliente(int id){
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(id == clientes[i]->getID()){
			for (int var = 0; var < transportes.size(); ++ var) {
				transportes[i]->sairCliente(clientes[i]);
			}
			clientes.erase(clientes.begin() + i);
			return true;
		}
	return false;
}
