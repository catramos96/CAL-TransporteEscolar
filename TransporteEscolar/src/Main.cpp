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

void menuVeiculos(Empresa *e){
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

void menuClientes(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuClientes();
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

void opMenuInicial(Empresa *e, int op) {
	switch (op) {
	case 0: { //veiculos
		menuVeiculos(e);
		break;
	}
	case 1: { //clientes
		menuClientes(e);
		break;
	}
	case 2: {//trajetos

		break;
	}
	case 3: { //sair
		//Guardar INFORMAÇÃO
		break;
	}
	}
}

void menuInicial(Empresa *e) {
	int op;
	do {
		try {
			clrscr();
			displayMenuInicial(e->getNome());
			opccao(op, 0, 3);
			opMenuInicial(e, op);
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
	} while (op != 3);
}




int main() {
	//temp
	/*
	Empresa *e = new Empresa("Transportes Escolares",Morada(1,1));
	menuInicial(e);
	esperar();
	//falta fazer deletes ---> estamos a usar new


	Empresa *e = new Empresa("Transportes Escolares", Morada(1,1));

	cout << "Empresa : " << e->getNome();

	//inscrever um cliente

	Cliente *c1 = new Cliente("Ines Gomes", Morada(2,1), Morada(3,1));
	Cliente *c2 = new Cliente("Andreia Rodrigues", Morada(2,2), Morada(3,1));
	e->addCliente(c1);
*/

	Empresa e = Empresa("GandaEmpresa", Morada(100,100,0));
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
	/*
	Mapa m = Mapa();
	m.setPontoInteresse(Morada(200,100,1));
	m.setPontoInteresse(Morada(100,200,4));

	m.displayMapa();
	*/
	getchar();
	return 0;
}
