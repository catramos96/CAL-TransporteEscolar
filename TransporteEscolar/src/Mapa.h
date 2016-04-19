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
	void displayMapa(vector<Morada> points);
	void setPontoInteresse(Morada m, bool b);
	bool isPontoInteresse(Morada m);
	//int isPonto(Morada m) const; // retorna o id se encontrou ou -1 caso não tenha encontrado
	int displayPontos() const;
	Morada getPonto(int id);
	vector<Morada> shortestPath(vector<Morada> points);
	Vertex<Morada> * getPontoVertex(int id);
	vector<Morada> getInterestPoints() const;
};


#endif /* SRC_MAPA_H_ */
