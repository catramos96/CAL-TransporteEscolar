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
	int x; //coordenada x
	int y; //coordenada y
	int id; //id da morada -> correspondente numerico a uma morada (é unico)
public:
	Morada(){};
	Morada(int x, int y, int id);
	bool operator == (const Morada &m) const;
	int getID() const;
	int getX() const;
	int getY() const;
};

#endif /* SRC_MORADA_H_ */
