#include "Veiculo.h"
#include <algorithm>

using namespace std;

Veiculo::Veiculo(int numLugares, string matricula){
	this->numLugares = numLugares;
	this->matricula = matricula;
}

int Veiculo::getNumLugares()const{
	return numLugares;
}

string Veiculo::getMatricula()const {
	return matricula;
}

bool Veiculo::addCliente(Cliente *c){
	//não excede o número de lugares
	if(numLugares > clientes.size() && !existeCliente(c)){
		clientes.push_back(c);
		numLugares++;
		return true;
	}
	return false;
}

bool Veiculo::sairCliente(Cliente *c){
	if(!existeCliente(c))
		return false;

	vector<Cliente *>::iterator it;
	it = find(clientes.begin(),clientes.end(),c);
	clientes.erase(it);
	numLugares--;
	return true;
}

bool Veiculo::existeCliente(Cliente *c) const{
	vector<Cliente *>::const_iterator it;
	if(find(clientes.begin(),clientes.end(),c) != clientes.end())
		return true;
	return false;
}

bool Veiculo::passaNaEscola(Morada escola) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
	vector<Cliente *>::const_iterator itf = clientes.end();

	while(itb != itf){
		if((*itb)->getEscola() ==escola)
			return true;
		itb++;
	}
	return false;
}


