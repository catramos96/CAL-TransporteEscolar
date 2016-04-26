#include "Cliente.h"

using namespace std;

/*
 * @brief Inicializacao do membro estatico id da classe Cliente.
 */
int Cliente::id = 1;

/****************************
 * CONSTRUTOR
 ***************************/

/*
 * @brief Contrutor da Classe Cliente
 * @param nome (string)
 * @param casa (Morada *)
 * @param escola (Morada *)
 */
Cliente::Cliente(string nome, Morada *casa, Morada *escola) : ID(id++){
	this->nome = nome;
	this->residencia = casa;
	this->escola = escola;
}

/*
 * @brief Construtor da Classe Cliente
 * @param nome (string)
 * @param casa (Morada *
 */
Cliente::Cliente(string nome, Morada *casa): ID(id++){
	this->nome = nome;
	this->residencia = casa;
	this->escola = NULL;
}

/****************************
 * GETS
 ***************************/

/*
 * @brief Funcao que retorna o nome do Cliente.
 * @return nome (string)
 */
string Cliente::getNome() const{
	return nome;
}

/*
 * @brief Funcao que retorna a escola de um Cliente.
 * @return escola (Morada *)
 */
Morada* Cliente::getEscola() const{
	return escola;
}

/*
 * @brief Funcao que retorna a residencia de um Cliente.
 * @return residencia (Morada *)
 */
Morada* Cliente::getResidencia() const{
	return residencia;
}

/*
 * @brief Funcao que retorna o id de um Cliente.
 * @return ID (int)
 */
int Cliente::getID() const{
	return ID;
}

/****************************
 * SETS
 ***************************/

/*
 * @brief Funcao que altera a residencia de um Cliente.
 * @param nova (Morada *), nova residencia
 */
void Cliente::setNovaResidencia(Morada *nova){
	residencia = nova;
}

/*
 * @brief Funcao que altera a escola de um Cliente.
 * @param nova (Morada *), nova escola
 */
void Cliente::setNovaEscola(Morada *nova){
	escola = nova;
}

/*
 * @brief Funcao que altera o id de um Cliente.
 * @param id (int)
 */
void Cliente::setID(int id){
	ID = id;
}

/****************************
 * OPERADORES
 ***************************/

/*
 * @brief Funcao de overloading do operator ==
 * @param c (Cliente)
 * @return bool
 */
bool Cliente::operator== (const Cliente &c) const{
	if(ID == c.getID())
		return true;
	else
		return false;
}

/*
 * @brief Funcao de overloading do operador <<.
 * @param o (ostream)
 * @param c (Cliente)
 * @return o (ostream)
 */
ostream & operator<<(ostream & o, const Cliente &c){
	o << "ID - " << c.getID() << " Nome -  "<< c.getNome() << " Residencia - " << *c.getResidencia()<< " Escola - " << *c.getEscola() ;
	return o;
}

