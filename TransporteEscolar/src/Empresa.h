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
	bool isEscola;
public:
	Empresa(string nome, Morada *endereco);
	string getNome() const;
	Morada* getEndereco() const;
	void setIsEscola(bool b);
	bool getIsEscola() const;
	vector<Morada *> getEscolas() const;
	void setNome(string nome);
	void setEndereco(Morada *endereco);
	Mapa* getMapa() const;
	vector<Cliente *> getClientesEscola(Morada *escola) const;
	vector<Cliente *> getClientesPontoRecolha(Morada * ponto) const;
	void setClientesPI(int id);
	void setMapa(Mapa* m);
	bool addTransporte(Veiculo * veiculo);
	bool addCliente(Cliente *cliente);
	bool addEscola(Morada * e);
	bool removeTransporte(Veiculo * veiculo);
	bool removeCliente(Cliente * cliente);
	bool removerEscola(Morada *e);
	bool removeCliente(int id);
	void guardarInfo() const;
	void carregarInfo() ;
	bool displayTrajetosIda(string matricula);
	bool displayTrajetosVolta(string matricula);
	void displayMapa(vector<Morada> points);
	void displayClientes() const;
	void displayVeiculos() const;
	void displayEscolas() const;
	void displayPontosRecolha() const;
	void distribuiCliVeiculos();
	void initialization();
	void update();
	bool todosPontosRecolhaAtingiveis();
};

#endif /* SRC_EMPRESA_H_ */
