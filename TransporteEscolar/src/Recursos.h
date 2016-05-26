#include <iostream>
#include <Windows.h>
#include <string>
#include "Excecoes.h"

using namespace std;

/**
 * @brief Funcao de display de um titulo
 * @param t (string)
 */
void displayTitulo(string t){
	cout << "///////////////////////////////\n";
	cout << "// " << t << endl;
	cout << "///////////////////////////////\n\n";
}

/**
 * @brief Funcao de display do menu inicial
 * @param nome_empresa (string)
 */
void displayMenuInicial(string nome_empresa){
	displayTitulo(nome_empresa);
	cout << "1 - Veiculos\n";
	cout << "2 - Clientes\n";
	cout << "3 - Pontos de Recolha\n";
	cout << "4 - Escolas\n";
	cout << "5 - Arestas Bloqueadas\n";
	cout << "6 - Sair\n";
}

/**
 * @brief Funcao de display do menu veiculos
 */
void displayMenuVeiculos(){
	displayTitulo("VEICULOS");
	cout << "1 - Adicionar Veiculo\n";
	cout << "2 - Remover Veiculo\n";
	cout << "3 - Ver Veiculos\n";
	cout << "4 - Ver Trajeto Ida\n";
	cout << "5 - Ver Trajeto Volta\n";
	cout << "6 - Voltar Atras\n";
}

/**
 * @brief Funcao de display do menu clientes
 */
void displayMenuClientes(){
	displayTitulo("CLIENTES");
	cout << "1 - Adicionar Clientes\n";
	cout << "2 - Remover Clientes\n";
	cout << "3 - Ver Clientes\n";
	cout << "4 - Pesquisar Clientes\n";
	cout << "5 - Pesquisar Clientes por Morada\n";
	cout << "6 - Voltar Atras\n";
}

/**
 * @brief Funcao de display do menu pontos de interesse (recolha)
 */
void displayMenuPI(){
	displayTitulo("PONTOS DE RECOLHA");
	cout << "1 - Adicionar Ponto\n";
	cout << "2 - Remover Ponto\n";
	cout << "3 - Ver Pontos de recolha\n";
	cout << "4 - Procurar Pontos Recolha\n";
	cout << "5 - Voltar Atras\n";
}

void displayMenuArestas(){
	displayTitulo("ARESTAS BLOQUEADAS");
	cout << "1 - Bloquear Aresta\n";
	cout << "2 - Desbloquear Aresta\n";
	cout << "3 - Voltar Atras\n";
}
/**
 * @brief Funcao de display do menu escolas
 */
void displayMenuEscolas(){
	displayTitulo("ESCOLAS");
	cout << "1 - Ver Escolas\n";
	cout << "2 - Ver Alunos por escola\n";
	cout << "3 - Voltar Atras \n";
}

/**
 * @brief Funcao que verifica se a opcao escolhida esta entre os valores aceites.
 * Caso nao esteja, lanca uma excessao.
 * @param op (int), opcao
 * @param min (int), valor minimo
 * @param max (int), valor maximo
 */
void opccao(int &op, int min, int max) {
	cout << "Seleccione uma opccao: ";
	cin >> op;
	if (op < min || op > max) {
		cin.clear();
		cin.ignore(1000, '\n');
		throw OpccaoInvalida<int>(op, min, max);
	}
}

/**
 * @brief Funcao que obriga o utilizador a carregar numa tecla para avancar.
 */
void esperar() {
	system("pause");
}

/**
 * @brief Funcao que limpa o ecra da consola.
 */
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
