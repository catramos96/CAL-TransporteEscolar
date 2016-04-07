#include "Morada.h"

using namespace std;

Morada::Morada(int x, int y){
	this->x = x;
	this->y = y;
}

bool Morada::operator ==(const Morada &m) const{
	return (m.x == x && m.y == y);
}
