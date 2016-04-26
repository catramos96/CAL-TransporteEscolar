#ifndef SRC_VEICULO_H_
#define SRC_VEICULO_H_

#include <iostream>
#include <vector>
#include "Cliente.h"
#include "Mapa.h"

using namespace std;

class Veiculo{
private:
	unsigned int numLugares;
	string matricula;
	vector<Cliente *> clientes;
	vector<Morada > caminho;
public:
	//Construtores
	Veiculo(string matricula, int numLugares);
	//Gets
	int getNumLugares()const;
	string getMatricula()const;
	vector<Cliente *> getClientes() const;
	vector<Morada> getCaminho();
	int lugaresLivres();
	//Adicionar
	bool addCliente(Cliente *c);
	void pushCaminho(Morada m);
	//Remover
	bool sairCliente(Cliente *c);
	//Confirmar
	bool existeCliente(Cliente *c)const;
	bool passaNaEscola(Morada *escola)const;
	//Operators
	bool operator== (const Veiculo &v) const;
	friend ostream & operator<<(ostream & o, const Veiculo &v);


};

#endif /* SRC_VEICULO_H_ */
