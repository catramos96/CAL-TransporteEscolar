#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_

#include <iostream>
#include "Morada.h"
#include "Veiculo.h"
#include "Cliente.h"

using namespace std;

class Empresa{
private:
	string nome;
	Morada endereco;
	vector<Veiculo *> transportes;
	vector<Cliente *> clientes;
	vector<Morada *> escolas;
	//Mapa mapa; //mapa da cidade
public:
	Empresa(string nome, Morada endereco);
	string getNome() const;
	Morada getEndereco() const;
	void setNome(string nome);
	void setEndereco(Morada endereco);
	bool addTransporte(Veiculo * veiculo);
	bool addCliente(Cliente *cliente);
	bool removeTransporte(Veiculo * veiculo);
	bool removeCliente(Cliente * cliente);
	void distribuiCliVeiculos();
	void enviaVeiculos();
	void displayClientes() const;
	bool removeCliente(int id);
};

#endif /* SRC_EMPRESA_H_ */
