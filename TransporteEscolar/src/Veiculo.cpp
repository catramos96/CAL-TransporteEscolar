#include "Veiculo.h"
#include <algorithm>

using namespace std;

Veiculo::Veiculo(string matricula, int numLugares){
	this->matricula = matricula;
	this->numLugares = numLugares;
}

int Veiculo::getNumLugares()const{
	return numLugares;
}

string Veiculo::getMatricula()const {
	return matricula;
}

vector<Cliente *> Veiculo::getClientes() const{
	return clientes;
}

bool Veiculo::addCliente(Cliente *c){
	//não excede o número de lugares
	if(numLugares > clientes.size() && !existeCliente(c)){
		clientes.push_back(c);
		return true;
	}
	return false;
}

bool Veiculo::sairCliente(Cliente *c){
	vector<Cliente *>::iterator itb = clientes.begin();
	vector<Cliente *>::iterator itf = clientes.end();

	while(itb != itf){
		if(*(*itb) == *c)
		{
			clientes.erase(itb);
			return true;
		}
	}
	return false;
}

bool Veiculo::existeCliente(Cliente *c) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
		vector<Cliente *>::const_iterator itf = clientes.end();

		while(itb != itf){
			if(*(*itb) == *c)
			{
				return true;
			}
			itb++;
		}
		return false;
}

bool Veiculo::passaNaEscola(Morada *escola) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
	vector<Cliente *>::const_iterator itf = clientes.end();

	while(itb != itf){
		if(*(*itb)->getEscola() == *escola)
			return true;
		itb++;
	}
	return false;
}

// confirmar se está tudo fixe aqui
bool Veiculo::operator== (const Veiculo &v) const{
	if (matricula == v.getMatricula())
		return true;
	else
		return false;
}

int Veiculo::lugaresLivres(){

	return (numLugares - clientes.size());
}

void Veiculo::pushCaminho(Morada m){
	caminho.push_back(m);
}

vector<Morada> Veiculo::getCaminho(){
	return caminho;
}


ostream & operator<<(ostream & o, const Veiculo &v){
	o << "Matricula - " << v.getMatricula() << " Capacidade -  "<< v.getNumLugares();// << " Clientes - " << v.getClientes().size();
	return o;
}
