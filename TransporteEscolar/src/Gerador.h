#ifndef SRC_GERADOR_H_
#define SRC_GERADOR_H_

#include "Mapa.h"
#include "Empresa.h"
using namespace std;

class Gerador{
private:
	Empresa *e;
public:
	Gerador(int numNomes, bool escola);
	Empresa *getEmpresa();
};

#endif
