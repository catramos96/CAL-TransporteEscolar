#include "Morada.h"

using namespace std;

Morada::Morada(int x, int y, int id){
	this->x = x;
	this->y = y;
	this->id = id;
}

bool Morada::operator ==(const Morada &m) const{
	return (m.x == x && m.y == y);
}

int Morada::getID() const{
	return id;
}

int Morada::getX() const{
	return x;
}

int Morada::getY() const{
	return y;
}
