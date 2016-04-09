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
	return true;
}

bool Empresa::addCliente(Cliente * cliente)
{
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(cliente == clientes[i])
			return false;
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
			clientes.erase(clientes.begin() + i);
			return true;
		}
	return false;
}
