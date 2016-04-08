/*
 * Morada.h
 *
 *  Created on: 06/04/2016
 *      Author: Inês Gomes
 */

#ifndef SRC_MORADA_H_
#define SRC_MORADA_H_

#include <iostream>

using namespace std;

class Morada{
private:
	/*
	string rua;
	string localidade;
	string pais;
	string codigoPostal;
	*/
	int x;
	int y; // fica assim enquanto não soubermos como é porque é mais simples
public:
	Morada(){};
	Morada(int x, int y);
	bool operator == (const Morada &m) const;
};

#endif /* SRC_MORADA_H_ */
