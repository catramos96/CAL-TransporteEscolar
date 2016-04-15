#include "Graph.h"
#include "Empresa.h"
#include "Recursos.h"
#include "Excessoes.h"
#include "Mapa.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
/*
 * VERIFICAR se quando se remove um cliente, se existe mais algum cliente que marca
 * a escola ou a aquela casa , caso contrario deixam de ser pontos de interesse no mapa
 */
void addCliente(Empresa *e, Mapa *m){
	string nome;
	Morada casa, escola;
	int id;

	clrscr();
	displayTitulo("ADICIONAR CLIENTE");
	cout << "Nome: ";
	cin >> nome;
	//getline(cin,nome); ???
	cout << "Morada Residencial: ";
	cin >> id;
	casa = m->getPonto(id);

	if(casa.getID() == -1){
		throw PontoInexistente(casa);
	}
	cout << "Morada Escolar: ";
	cin >> id;


	escola = m->getPonto(id);
	cout << escola;
	if(escola.getID() == -1){
		throw PontoInexistente(escola);
	}

	Cliente *c = new Cliente(nome,casa,escola);

	//É so a casa que passa a ser um ponto de interesse ?
	if(e->addCliente(c) == true){
		cout << "\n\nAdicionado com sucesso !\n";
		m->setPontoInteresse(casa);
	}
	else
		throw ClienteJaExiste(nome,escola,casa);
	esperar();
	throw VoltarAtras();
}

void removerCliente(Empresa *e){
	int id;

	clrscr();
	displayTitulo("ADICIONAR CLIENTE");
	e->displayClientes();
	cout << "\nDigite o ID do cliente que quer remover: ";
	cin >> id;

	if(!e->removeCliente(id) == true)
		throw ClienteInexistente(id);

	cout << "\n\nCliente Removido com sucesso !\n";
	esperar();
	throw VoltarAtras();
}

void verClientes(Empresa *e){
	clrscr();
	displayTitulo("CLIENTES");
	e->displayClientes();
	esperar();
	throw VoltarAtras();
}

void menuTrajetos(Mapa *m){
	clrscr();
	displayTitulo("PONTOS");
	m->displayPontos();
	esperar();
	throw VoltarAtras();
}

void menuVeiculos(Empresa *e, Mapa *m){
	clrscr();
	int op;
	do {
		displayMenuVeiculos();
		opccao(op, 0, 4);
		switch (op) {
		case 0: { //add

			break;
		}
		case 1: { //rem

			break;
		}
		case 2: {//ver

			break;
		}
		case 3: {//pesq. traj

			break;
		}
		case 4: {
			throw VoltarAtras();
			esperar();
			break;
		}
		}
	} while (1);
}

void menuClientes(Empresa *e, Mapa *m){
	int op;
	do {
		clrscr();
		displayMenuClientes();
		opccao(op, 0, 4);
		switch (op) {
		case 0: { //add
			addCliente(e,m);
			break;
		}
		case 1: { //rem
			removerCliente(e);
			break;
		}
		case 2: {//ver
			verClientes(e);
			break;
		}
		case 3: {//pesq. traj

			break;
		}
		case 4: {
			throw VoltarAtras();
			esperar();
			break;
		}
		}
	} while (1);
}

void opMenuInicial(Empresa *e, Mapa *m, int op) {
	switch (op) {
	case 0: { //veiculos
		menuVeiculos(e,m);
		break;
	}
	case 1: { //clientes
		menuClientes(e,m);
		break;
	}
	case 2: {//trajetos
		menuTrajetos(m);
		break;
	}
	case 3: { //sair
		//Guardar INFORMAÇÃO
		break;
	}
	}
}

void menuInicial(Empresa *e, Mapa *m) {
	int op;
	do {
		try {
			clrscr();
			displayMenuInicial(e->getNome());
			opccao(op, 0, 3);
			opMenuInicial(e, m, op);
		}
		catch (OpccaoInvalida<int>(x)) {
			cout << x.getOp() << " nao se encontra entre as opccoes "
					<< x.getMin() << " e " << x.getMax() << endl << endl;
			esperar();
		}
		catch (VoltarAtras) {
		}
		catch (InputFail) {
			cout << endl;
			esperar();
		}
		catch (ClienteJaExiste(e)){
			cout << "Ja existe o cliente com o nome " << e.getNome() << ", morada escolar " << e.getMoradaEscola() << " e residencia "<< e.getMoradaResidencia() << ".\n";
			esperar();
		}

		catch ( ClienteInexistente(e)){
			cout << "Nao existe um cliente com o id " << e.getID() << endl;
			esperar();
		}

		catch (PontoInexistente(e)){
			cout << "Nao existe no mapa um ponto " << e.getPonto() << endl;
			esperar();
		}
	} while (op != 3);
}




int main() {
	//temp

	Empresa *e = new Empresa("Transportes Escolares",Morada(1,1,0));
	Mapa *m = new Mapa();
	m->setPontoInteresse(Morada(200,100,1));
	m->setPontoInteresse(Morada(100,200,4));

	m->displayMapa();
	menuInicial(e,m);
	esperar();
	//falta fazer deletes ---> estamos a usar new

	delete(e);
	delete(m);


	/*Empresa e = Empresa("GandaEmpresa", Morada(100,100,0));
	Cliente *c1 = new Cliente("Ines Gomes", Morada(200,300,9), Morada(400,400,15));
	Cliente *c2 = new Cliente("Andreia Rodrigues", Morada(200,400,13), Morada(400,400,15));
	Cliente *c3 = new Cliente("Catarina Ramos", Morada(200,200,5), Morada(400,400,15));
	Veiculo *v1 = new Veiculo(15, "xx-11-yy");

	e.addTransporte(v1);
	e.addCliente(c1);
	e.addCliente(c2);
	e.addCliente(c3);

	e.distribuiCliVeiculos();
	e.enviaVeiculos();	//funcao que atualiza os mapas dos veiculos e faz display dos mesmos

Mapa m = Mapa();
	m.setPontoInteresse(Morada(200,100,1));
	m.setPontoInteresse(Morada(100,200,4));

	m.displayMapa();
	getchar();*/
	return 0;
}
