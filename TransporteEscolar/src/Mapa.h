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
	Graph<Morada> getMapa();
	void display();
	void displayMapa(vector<Morada> points);
	void setPontoInteresse(Morada m, bool b);
	bool isPontoInteresse(Morada m);
	//int isPonto(Morada m) const; // retorna o id se encontrou ou -1 caso não tenha encontrado
	int displayPontos() const;
	Morada getPonto(int id);
	vector<Morada> shortestPath(vector<Morada> points);
	Vertex<Morada> * getPontoVertex(int id);
	vector<Morada> getInterestPoints() const;
	int getMinDistBetweenPoints(int pi, vector<Morada> points, vector<Morada> &res);
	bool getPontoProcessado(Morada ponto);
	void setPontoProcessado(Morada ponto, bool estado);
	void makefloydWarshallShortestPath();
	double haversineAlgorith(double lat1, double long1, double lat2, double long2);
};


#endif /* SRC_MAPA_H_ */
