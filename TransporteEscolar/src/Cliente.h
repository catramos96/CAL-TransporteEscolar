#ifndef SRC_CLIENTE_H_
#define SRC_CLIENTE_H_

#include <iostream>

using namespace std;

class Cliente{
private:
	string nome;
	Morada escola;
	Morada endereco;
	static int id = 0;
public:
	Cliente(string nome, Morada casa, Morada escola);
	void setNovaResidencia(Morada nova);
	void setNovaEscola(Morada nova);
	Morada getEscola();
	Morada getResidencia();
};

#endif /* SRC_CLIENTE_H_ */
