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
	Mapa(GraphViewer *gv);
	Graph<Morada> getMapa();
	void display();
	void displayMapa(vector<Morada> points);
	void displayPath(GraphViewer *gv,vector<Morada> points, bool inverse);
	void setPontoInteresse(Morada m, bool b);
	bool isPontoInteresse(Morada m);
	int displayPontos() const;
	Morada getPonto(int id);
	//vector<Morada> shortestPath(vector<Morada> points);
	Vertex<Morada> * getPontoVertex(int id);
	vector<Morada> getInterestPoints() const;
	int getMinDistBetweenPoints(int pi, vector<Morada> points);
	bool getPontoProcessado(Morada ponto);
	void setPontoProcessado(Morada ponto, bool estado);
	void makefloydWarshallShortestPath();
	double haversineAlgorith(double lat1, double long1, double lat2, double long2);
	vector<Morada> makePath(vector<Morada> points);
	void cleanMapa(GraphViewer *gv);
};


#endif /* SRC_MAPA_H_ */
