#ifndef SRC_VEICULO_H_
#define SRC_VEICULO_H_

#include <iostream>
#include <vector>
#include "Cliente.h"

using namespace std;

class Veiculo{
private:
	unsigned int numLugares;
	string matricula;
	vector<Cliente *> clientes;
public:
	Veiculo(int numLugares, string matricula);
	int getNumLugares()const;
	string getMatricula()const;
	vector<Cliente *> getClientes() const;
	bool addCliente(Cliente *c);
	bool sairCliente(Cliente *c);
	bool existeCliente(Cliente *c)const;
	bool passaNaEscola(Morada escola)const;
	bool operator== (const Veiculo &v) const;
};

#endif /* SRC_VEICULO_H_ */
