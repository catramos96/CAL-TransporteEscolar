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

void Morada::setID(int id){
	this->id=id;
}

void Morada::setX(int x){
	this->x = x;
}

void Morada::setY(int y){
	this->y = y;
}

Morada & Morada::operator=(const Morada &m){
	x = m.getX();
	y = m.getY();
	id = m.getID();

	return *this;
}

ostream & operator<<(ostream & o, const Morada &m){
	o << m.getID()  << "(" << m.getX() << "," << m.getY() << ")";
	return o;
}
