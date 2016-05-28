#ifndef SRC_MAPA_H_
#define SRC_MAPA_H_

#include "Graph.h"
#include "Morada.h"
#include "graphviewer.h"

class Mapa{
private:
	Graph<Morada> mapa;
	int maxID;
public:
	Mapa(GraphViewer *gv);
	Graph<Morada> getMapa();
	void displayPath(GraphViewer *gv, vector<Morada> points, bool makePath);
	bool setPontoInteresse(Morada m, bool b);
	bool isPontoInteresse(Morada m);
	int displayPontos() const;
	Morada *getPonto(int id);
	Vertex<Morada> * getPontoVertex(int id);
	vector<Morada > getInterestPoints() const;
	int getMinDistBetweenPoints(int pi, vector<Morada > points);
	bool getPontoProcessado(Morada ponto);
	void setPontoProcessado(Morada ponto, bool estado);
	void makefloydWarshallShortestPath();
	double haversineAlgorith(double lat1, double long1, double lat2, double long2);
	vector<Morada> makePath(vector<Morada> points);
	void cleanMapa(GraphViewer *gv);
	void setBlockedEdge(int edgeId, bool state);
	void displayBlockedEdges();
	int getIDMax();
	vector<Morada> getAllMorada() const;
};


#endif /* SRC_MAPA_H_ */
