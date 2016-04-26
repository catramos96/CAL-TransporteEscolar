#include "Veiculo.h"
#include <algorithm>

using namespace std;

/****************************
 * CONSTRUTORES
 ***************************/

/**
 * @brief Contrutor da class Veiculo
 * @param matricula (string)
 * @param numLugares (int)
 */
Veiculo::Veiculo(string matricula, int numLugares){
	this->matricula = matricula;
	this->numLugares = numLugares;
}

/****************************
 * GETS
 ***************************/

/**
 * @brief Funcao que retorna o numero de lugares de um veiculo
 * @return numLugares (int)
 */
int Veiculo::getNumLugares()const{
	return numLugares;
}

/**
 * @brief Funcao que retorna a matricula do Veiculo
 * @return matricula (string)
 */
string Veiculo::getMatricula()const {
	return matricula;
}

/**
 * @brief Funcao que retorna um vector com os clientes que estao dentro do veiculo
 * @return clientes, vector<Cliente *>
 */
vector<Cliente *> Veiculo::getClientes() const{
	return clientes;
}

/**
 * @brief Funcao que retorna o caminho do Veiculo
 * @return caminho (vector<Morada>)
 */
vector<Morada> Veiculo::getCaminho(){
	return caminho;
}

/**
 * @brief Funcao que retorna o numero de lugares livres do Veiculo
 * @return lugaresLivres (int)
 */
int Veiculo::lugaresLivres(){
	return (numLugares - clientes.size());
}

/****************************
 * ADICIONAR
 ***************************/

/**
 * @brief Funcao que adiciona um Cliente a um Veiculo e retorna um bool.
 * Se esse cliente ja foi adicionado, nao adiciona e retorna false
 * @param *c (Cliente)
 * @return bool, true sucesso, false erro/falha
 */
bool Veiculo::addCliente(Cliente *c){
	//não excede o número de lugares
	if(numLugares > clientes.size() && !existeCliente(c)){
		clientes.push_back(c);
		return true;
	}
	return false;
}

/**
 * @brief Funcao que adiciona ao vector<Morada> caminho uma Morada
 * @param m (Morada)
 * @return void
 */
void Veiculo::pushCaminho(Morada m){
	caminho.push_back(m);
}

/****************************
 * REMOVER
 ***************************/

/**
 * @brief Funcao que remove um Cliente do Veiculo
 * @param *c (Cliente)
 * @return bool, true sucesso, false erro/falha
 */
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

/****************************
 * CONFIRMAR
 ***************************/

/**
 * @brief Funcao que retorna um bool sobre a existencia de um Cliente
 * @param *c (Cliente)
 * @return bool, true existe, false nao existe
 */
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

/**
 * @brief Funcao que retorna um bool sobre se o Veiculo passa numa determinada Escola
 * @param *escola (Morada)
 * @return bool
 */
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

/****************************
 * OPERATORS
 ***************************/

/**
 * @brief Funcao de overloading do operador ==
 * @param v (Veiculo)
 * @return bool
 */
bool Veiculo::operator== (const Veiculo &v) const{
	if (matricula == v.getMatricula())
		return true;
	else
		return false;
}

/**
 * @brief Funcao de overloading do operador <<
 * @param o (ostream)
 * @param v (Veiculo)
 * @return o (ostream)
 */
ostream & operator<<(ostream & o, const Veiculo &v){
	o << "Matricula - " << v.getMatricula() << " Capacidade -  "<< v.getNumLugares();// << " Clientes - " << v.getClientes().size();
	return o;
}
