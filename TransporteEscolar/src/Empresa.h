#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_

#include <iostream>
#include "Morada.h"
#include "Veiculo.h"
#include "Cliente.h"
#include "Mapa.h"

using namespace std;

class Empresa{
private:
	string nome;
	Morada *endereco;
	vector<Veiculo *> transportes;
	vector<Cliente *> clientes;
	vector<Morada *> escolas;
	Mapa* mapa; //mapa da cidade
	GraphViewer *gv;
	bool isEscola;
public:
	Empresa();
	string getNome() const;
	Morada* getEndereco() const;
	void setIsEscola(bool b);
	bool getIsEscola() const;
	vector<Morada *> getEscolas() const;
	void setNome(string nome);
	void setEndereco(Morada *endereco);
	Mapa* getMapa() const;
	GraphViewer * getGV() {return gv;}
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
	bool displayTrajetosIda(string matricula);
	bool displayTrajetosVolta(string matricula);
	void displayMapa(vector<Morada> points);
	void displayClientes() const;
	void displayVeiculos() const;
	void displayEscolas() const;
	void displayPontosRecolha();
	void distribuiCliVeiculos();
	void initialization();
	void update();
	bool todosPontosRecolhaAtingiveis();
	int changeNumCriancas(Morada m, int state);

	//==========================================================================================//
	// NOVOS MÉTODOS CRIADOS PARA O SEGUNDO TRABALHO
	//==========================================================================================//

	void readLast();	//le o ficheiro last.txt
	void writeLastAndInfo();
	void fillEmpresa(string nome, int id, bool isEsc, vector<int> escolasID, int numCriancas);
	void hasPR(Morada *m);	//verifica se um dado ponto é ponto de recolha
	void displayClientesMorada(string morada);

	vector<Cliente> exactSearch(string morada); //usa algoritmo Exato
	void proximitySearchMorada(vector<Morada> moradas, string toSearch); //usa algoritmo Aproximado
	void proximitySearchClient(string nome);				//usa algoritmo Aproximado

	void exactSearch4Test(string nome);	//metodo usado para testes de tempos

	// algoritmos com strings
	int distanceAlgorithm(string street,string streetToSearch);
	int kmp(string text, string pattern);
	vector<int> prefixFunction(string pattern);
	int min(int x, int y, int z);
};

#endif /* SRC_EMPRESA_H_ */
