#ifndef SRC_MAPA_H_
#define SRC_MAPA_H_

#include "Graph.h"
#include "Morada.h"
#include "graphviewer.h"

class Mapa{
private:
	Graph<Morada> mapa;
public:
	Mapa();
	void displayMapa();
	void setPontoInteresse(Morada m);
	bool isPontoInteresse(Morada m);
};


#endif /* SRC_MAPA_H_ */
