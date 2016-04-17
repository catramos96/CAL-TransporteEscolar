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

vector<Cliente *> Veiculo::getClientes() const{
	return clientes;
}

bool Veiculo::addCliente(Cliente *c){
	//n�o excede o n�mero de lugares
	if(numLugares > clientes.size() && !existeCliente(c)){
		clientes.push_back(c);
		numLugares++;
		return true;
	}
	return false;
}

bool Veiculo::sairCliente(Cliente *c){
	vector<Cliente *>::iterator it;
	cout << "vou mand�lo com o crl" << endl;
	if(find(clientes.begin(),clientes.end(),c) != clientes.end())
	{	clientes.erase(it);
	numLugares--;
	cout << "wooo encontrei" << endl;
	return true;
	}
	cout << "n encontrei" << endl;
	return false;
}

bool Veiculo::existeCliente(Cliente *c) const{
	vector<Cliente *>::const_iterator it;
	if(find(clientes.begin(),clientes.end(),c) != clientes.end())
		return true;
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

// confirmar se est� tudo fixe aqui
bool Veiculo::operator== (const Veiculo &v) const{
	if (matricula == v.getMatricula())
		return true;
	else
		return false;
}

int Veiculo::lugaresLivres(){
	return (numLugares - clientes.size());
}

void Veiculo::setPartida(Morada *partida){
	this->partida = partida;
}

void Veiculo::setDestino(Morada *destino){
	this->destino = destino;
}

/**
 * cria um vetor de pontos de interesse para esse veiculo
 */
vector<Morada> Veiculo::makePath(){

	vector<Morada> points;

	points.push_back(*partida);
	for(size_t i = 0; i < clientes.size(); i++)
		points.push_back(*clientes.at(i)->getResidencia());
	points.push_back(*destino);

	return points;
}

Morada* Veiculo::getPartida() const{
	return partida;
}

Morada* Veiculo::getDestino() const{
	return destino;
}

ostream & operator<<(ostream & o, const Veiculo &v){
	o << "Matricula - " << v.getMatricula() << " Capacidade -  "<< v.getNumLugares();
	if(v.getPartida() != NULL)
		o << " Partida - "<< *v.getPartida() ;
	if(v.getDestino() != NULL)
		o << " Destino - " << *v.getDestino();
	return o;
}
