#include "Morada.h"

using namespace std;

/****************************
 * CONSTRUTORES
 ***************************/

/**
 * @brief Construtor default da classe Morada
 */
Morada::Morada(){
}

/**
 * @brief Construtor da classe Morada
 * @param x (double), coordenada x
 * @param y (double), coordenada y
 * @param id (int), id do vertice correspondente
 */
Morada::Morada(double x, double y, int id, string nome){
	this->id = id;
	this->numCriancas = 0;
	this->x = x;
	this->y = y;
	this->nome = nome;
}

/****************************
 * GETS
 ***************************/

/**
 * @brief Funcao que retorna o id da Morada
 * @return id (int)
 */
int Morada::getID() const{
	return id;
}

/**
 * @brief Funcao que retorna a coordenada x da Morada
 * @return x (double)
 */
double Morada::getX() const{
	return x;
}

/**
 * @brief Funcao que retorna a coordenada y da Morada
 * @return y (double)
 */
double Morada::getY() const{
	return y;
}

/**
 * @brief Funcao que retorna o numero de criancas nesta Morada (ponto de recolha)
 * @return numCriancas (int)
 */
int Morada::getNumCriancas() const{
	return numCriancas;
}

string Morada::getNome() const{
	return nome;
}

/****************************
 * SETS
 ***************************/

/**
 * @brief Funcao que altera o id da Morada
 * @param id (int)
 */
void Morada::setID(int id){
	this->id=id;
}

/**
 * @brief Funcao que altera a coordenada x da Morada
 * @param x (double)
 */
void Morada::setX(double x){
	this->x = x;
}

/**
 * @brief Funcao que altera a coordenada y da Morada
 * @param y (double)
 */
void Morada::setY(double y){
	this->y = y;
}

/**
 * @brief Funcao que incrementa o numero de criancas nessa Morada (ponto de recolha)
 */
void Morada::incNumCriancas(){
	numCriancas++;
}

/**
 * @brief Funcao que descrementa o numero de criancas nessa Morada (ponto de recolha)
 */
void Morada::decNumCriancas(){
	if(numCriancas > 0)
		numCriancas--;
}

/****************************
 * OPERADORES
 ***************************/

/**
 * @brief Funcao de overloading do operador =
 * @param m (Morada)
 * @return *this (Morada)
 */
Morada & Morada::operator=(const Morada &m){
	x = m.getX();
	y = m.getY();
	id = m.getID();

	return *this;
}

/**
 * @brief Funcao de overloading do operador <<
 * @param o (ostream)
 * @param m (Morada)
 * @return o (ostream)
 */
ostream & operator<<(ostream & o, const Morada &m){
		o << m.getID() << " " << m.getNome() << " ";
	return o;
}

/**
 * @brief Funcao de overloading do operador ==
 * @param m (Morada)
 * @return bool
 */
bool Morada::operator ==(const Morada &m) const{
	return (m.id == id);
}

void Morada::setNumCriancas(int n){
	numCriancas = n;
}

