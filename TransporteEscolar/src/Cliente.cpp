#include "Cliente.h"

using namespace std;

Cliente::Cliente(string nome, Morada casa, Morada escola){
	this->nome = nome;
	this->endereco = casa;
	this->escola = escola;
	id++;
}

void Cliente::setNovaResidencia(Morada nova){
	endereco = nova;
}

void Cliente::setNovaEscola(Morada nova){
	escola = nova;
}

Morada Cliente::getResidencia(){
	return endereco;
}

Morada Cliente::getEscola(){
	return escola;
}


