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

// confirmar se está tudo fixe aqui
bool Veiculo::operator== (const Veiculo &v) const{
	if((numLugares == v.getNumLugares()) && (matricula == v.getMatricula()))
	{
		if(clientes.size() == v.getClientes().size())
		{
			for(unsigned int i = 0; i < clientes.size(); i++)
			{
				if(clientes[i] != v.getClientes()[i])
					return false;
			}
			return true;
		}
	}
	else
		return false;
}

int Veiculo::lugaresLivres(){
	return (numLugares - clientes.size());
}

void Veiculo::setPartida(Morada partida){
	this->partida = partida;
}

void Veiculo::setDestino(Morada destino){
	this->destino = destino;
}

/**
 * NAO ESTA ACABADO
 */
void Veiculo::makeMapa(){

	//1º atualiza os pontos de interesse
	mapa.setPontoInteresse(partida);
	mapa.setPontoInteresse(destino);

	for(int i = 0; i < clientes.size(); i++)
		mapa.setPontoInteresse(clientes.at(i)->getResidencia());

	//2º calcula o caminho mais curto
}

/**
 * NAO ESTA ACABADO
 */
void Veiculo::displayMapa(){
	//pode ser necessario funcoes que abrem e fecham as janelas
	mapa.displayMapa();
}
