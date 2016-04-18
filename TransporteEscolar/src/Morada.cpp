#include "Morada.h"

using namespace std;

Morada::Morada(double x, double y, int id){
	this->x = x;
	this->y = y;
	this->id = id;
}

bool Morada::operator ==(const Morada &m) const{
	return (m.id == id);
}

int Morada::getID() const{
	return id;
}

double Morada::getX() const{
	return x;
}

double Morada::getY() const{
	return y;
}

void Morada::setID(int id){
	this->id=id;
}

void Morada::setX(double x){
	this->x = x;
}

void Morada::setY(double y){
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
