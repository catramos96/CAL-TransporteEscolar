#include "Cliente.h"

using namespace std;

int Cliente::id = 0;

Cliente::Cliente(string nome, Morada casa, Morada escola) : ID(id++){
	this->nome = nome;
	this->residencia = casa;
	this->escola = escola;
}

string Cliente::getNome() const{
	return nome;
}

Morada Cliente::getEscola() const{
	return escola;
}

Morada Cliente::getResidencia() const{
	return residencia;
}

int Cliente::getID() const{
	return ID;
}

void Cliente::setNovaResidencia(Morada nova){
	residencia = nova;
}

void Cliente::setNovaEscola(Morada nova){
	escola = nova;
}

bool Cliente::operator== (const Cliente &c) const{
	if(nome == c.getNome() && escola == c.getEscola() && residencia == c.getResidencia() && ID == c.getID())
		return true;
	else
		return false;
}

