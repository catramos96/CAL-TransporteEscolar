/*
 * Cliente.h
 *
 *  Created on: 06/04/2016
 *      Author: In�s Gomes
 */

#include <iostream>

using namespace std;

class Cliente{
private:
	string nome;
	Morada escola;
	Morada endereco;
	static int id;
public:
	Cliente(string nome);
};
