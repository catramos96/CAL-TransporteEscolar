#ifndef SRC_CLIENTE_H_
#define SRC_CLIENTE_H_

#include <iostream>
#include "Morada.h"

using namespace std;

class Cliente{
private:
	string nome;
	Morada * escola;
	Morada * residencia;
	int ID; //relativo a um objeto
public:
	static int id; //global
	Cliente(string nome, Morada *casa, Morada *escola);
	Cliente(string nome, Morada *casa);
	string getNome() const;
	Morada * getEscola() const;
	Morada * getResidencia() const;
	int getID() const;
	void setNovaResidencia(Morada * nova);
	void setNovaEscola(Morada * nova);
	void setID(int id);
	bool operator== (const Cliente &c) const;
	friend ostream & operator<<(ostream & o, const Cliente &c);
};

#endif /* SRC_CLIENTE_H_ */
