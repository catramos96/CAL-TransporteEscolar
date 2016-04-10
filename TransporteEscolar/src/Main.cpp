#include <iostream>
#include "Graph.h"
#include "Empresa.h"
#include "Recursos.h"
#include "Excessoes.h"
#include <string>

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
	Empresa *e = new Empresa("Transportes Escolares",Morada(1,1));
	menuInicial(e);
	esperar();

	return 0;
}
