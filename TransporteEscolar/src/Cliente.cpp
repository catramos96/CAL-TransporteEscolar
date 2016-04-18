#include "Cliente.h"

using namespace std;

int Cliente::id = 1;

Cliente::Cliente(string nome, Morada *casa, Morada *escola) : ID(id++){
	this->nome = nome;
	this->residencia = casa;
	this->escola = escola;
}

string Cliente::getNome() const{
	return nome;
}

Morada* Cliente::getEscola() const{
	return escola;
}

Morada* Cliente::getResidencia() const{
	return residencia;
}

int Cliente::getID() const{
	return ID;
}

void Cliente::setNovaResidencia(Morada *nova){
	residencia = nova;
}

void Cliente::setNovaEscola(Morada *nova){
	escola = nova;
}

bool Cliente::operator== (const Cliente &c) const{
	if(ID == c.getID())
		return true;
	else
		return false;
}

ostream & operator<<(ostream & o, const Cliente &c){
	o << "ID - " << c.getID() << " Nome -  "<< c.getNome() << " Escola - " << *c.getEscola() << " Residencia - " << *c.getResidencia();
	return o;
}

