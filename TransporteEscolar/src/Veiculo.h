/*
 * Veiculo.h
 *
 *  Created on: 06/04/2016
 *      Author: In�s Gomes
 */

#ifndef SRC_VEICULO_H_
#define SRC_VEICULO_H_

#include <iostream>

using namespace std;

class Veiculo{
private:
	int numLugares;
	string matricula;
	vector<Cliente *> clientes;
public:
	Veiculo(int numLugares, string matricula);

};




#endif /* SRC_VEICULO_H_ */
