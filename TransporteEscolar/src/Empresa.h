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
	Morada *endereco;
	vector<Veiculo *> transportes;
	vector<Cliente *> clientes;
	vector<Morada *> escolas;
	Mapa* mapa; //mapa da cidade
public:
	Empresa(string nome, Morada *endereco);
	string getNome() const;
	Morada* getEndereco() const;
	vector<Morada *> getEscolas() const;
	void setNome(string nome);
	void setEndereco(Morada *endereco);
	bool addTransporte(Veiculo * veiculo);
	bool addCliente(Cliente *cliente);		//Verificar se a casa não é uma escola, e se a escola não é uma casa
	bool addEscola(Morada * e);
	bool removeTransporte(Veiculo * veiculo);
	bool removeCliente(Cliente * cliente);
	bool removerEscola(Morada *e);
	void distribuiCliVeiculos();
	void enviaVeiculos();
	void displayClientes() const;
	void displayVeiculos() const;
	void displayEscolas() const;
	bool removeCliente(int id);
	void displayMapa(vector<Morada> points);
	void guardarInfo() const;
	void carregarInfo() ;
	Mapa* getMapa() const;
	vector<Cliente *> getClientesEscola(Morada *escola) const;
};

#endif /* SRC_EMPRESA_H_ */
