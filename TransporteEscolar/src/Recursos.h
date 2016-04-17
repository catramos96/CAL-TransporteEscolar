#include <iostream>
#include <Windows.h>
#include "Excessoes.h"
#include <string>

using namespace std;

void displayTitulo(string t){
	cout << "///////////////////////////////\n";
	cout << "// " << t << endl;
	cout << "///////////////////////////////\n\n";
}

void displayMenuInicial(string nome_empresa){
	displayTitulo(nome_empresa);
	cout << "0 - Veiculos\n";
	cout << "1 - Clientes\n";
	cout << "2 - Trajetos\n";
	cout << "3 - Escolas\n";
	cout << "4 - Sair\n";
}

void displayMenuVeiculos(){
	displayTitulo("VEICULOS");
	cout << "0 - Adicionar Veiculo\n";
	cout << "1 - Remover Veiculo\n";
	cout << "2 - Ver Veiculos\n";
	cout << "3 - Procurar por trajeto\n";
	cout << "4 - Voltar Atras\n";
}

void displayMenuClientes(){
	displayTitulo("CLIENTES");
	cout << "0 - Adicionar Clientes\n";
	cout << "1 - Remover Clientes\n";
	cout << "2 - Ver Clientes\n";
	cout << "3 - Procurar por trajeto\n";
	cout << "4 - Voltar Atras\n";
}

void opccao(int &op, int min, int max) {
	cout << "Seleccione uma opccao: ";
	cin >> op;
	if (op < min || op > max) {
		cin.clear();
		cin.ignore(1000, '\n');
		throw OpccaoInvalida<int>(op, min, max);
	}
}

void esperar() {
	system("pause");
}

//Clears the screen

void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}
