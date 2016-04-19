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
	double x; //coordenada x
	double y; //coordenada y
	int id; //id da morada -> correspondente numerico a uma morada (é unico)
	int numCriancas;
public:
	Morada(){};
	Morada(double x, double y, int id);
	bool operator == (const Morada &m) const;
	int getID() const;
	double getX() const;
	double getY() const;
	void setID(int id);
	void setX(double x);
	void setY(double y);
	void incNumCriancas();
	void decNumCriancas();
	int getNumCriancas() const;
	Morada & operator=(const Morada &m);
	friend ostream & operator<<(ostream & o, const Morada &m);

};

#endif /* SRC_MORADA_H_ */
