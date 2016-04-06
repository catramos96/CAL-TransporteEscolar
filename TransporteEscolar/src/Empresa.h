/*
 * Empresa.h
 *
 *  Created on: 06/04/2016
 *      Author: In�s Gomes
 */

#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_

#include <iostream>

using namespace std;

class Empresa{
private:
	string nome;
	Morada endereco;
	vector<Veiculo *> transportes;
	vector<Cliente *> clientes;
public:
	Empresa();
};



#endif /* SRC_EMPRESA_H_ */
