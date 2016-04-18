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
	Morada *partida;
	Morada *destino;
public:
	Veiculo(int numLugares, string matricula);
	int getNumLugares()const;
	string getMatricula()const;
	vector<Cliente *> getClientes() const;
	bool addCliente(Cliente *c);
	bool sairCliente(Cliente *c);
	bool existeCliente(Cliente *c)const;
	bool passaNaEscola(Morada *escola)const;
	bool operator== (const Veiculo &v) const;
	int lugaresLivres();
	void setPartida(Morada *partida);
	void setDestino(Morada *destino);
	vector<Morada> makePath();
	Morada* getPartida() const;
	Morada* getDestino() const;
	//enviar clientes, desmarcar pontos de interesse e marcar os que interessa
	friend ostream & operator<<(ostream & o, const Veiculo &v);
};

#endif /* SRC_VEICULO_H_ */
