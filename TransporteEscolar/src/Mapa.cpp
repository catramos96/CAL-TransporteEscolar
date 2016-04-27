#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * Construtor
 * Inicializa o grafo com os nos e arestas dos ficheiros "nos.txt" e "arestas.txt"
 */

// ALGORITMO PARA CALCULO DE DISTANCIAS - LAT E LONG EM RAD
double Mapa::haversineAlgorith(double lat1, double long1, double lat2, double long2)
{
	const int earthRadius = 6371000;
	double deltaLat = lat2 - lat1;
	double deltaLong = long2 - long1;

	double a = pow(sin(deltaLat/2), 2) + cos(lat1)*cos(lat2)*+pow(sin(deltaLong/2),2);
	double c = 2*atan2(sqrt(a),sqrt(1-a));
	double d = earthRadius * c;

	return d;
}

Mapa::Mapa(GraphViewer *gv){

	//openstreetmaps.org

	vector<int> twoWays; //se uma aresta estiver neste vértice significa que a sua rua é bidirecional
	vector<pair<unsigned int, unsigned int> > vertexIndex;
	vector<pair<unsigned int, pair<double, double> > > vertexCoord;
	double latMax, latMin, longMax, longMin;
	bool first = true;
	ifstream inFile;

	//--------------------------------------------- nos.txt----------------------------------------------//
	inFile.open("node.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	int idNo, newIdNo = 0;
	double x, y;
	string line;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;


		linestream >> idNo;
		getline(linestream, data, ';');  // discard lat in º
		getline(linestream, data, ';');  // discard long in º
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> x;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> y;

		Morada m = Morada(x,y,newIdNo);
		mapa.addVertex(m);

		if(first)
		{
			latMax = x;
			latMin = x;
			longMax = y;
			longMin = y;
		}
		else
		{
			if(x > latMax)
				latMax = x;
			if(y > longMax)
				longMax = y;
			if(x < latMin)
				latMin = x;
			if(y < longMin)
				longMin = y;
		}

		pair<double, double> coordinates(x,y);
		pair<unsigned int, pair<double, double> > idCoordinates(newIdNo, coordinates);
		vertexCoord.push_back(idCoordinates);

		pair<unsigned int, unsigned int> idPair;
		idPair.first = newIdNo;
		idPair.second = idNo;
		vertexIndex.push_back(idPair);
		newIdNo++;
		first = false;
	}

	inFile.close();

	for (unsigned int i = 0; i < vertexCoord.size(); i++)
	{
		int id = vertexCoord.at(i).first;
		double x =  vertexCoord.at(i).second.first;
		double y =  vertexCoord.at(i).second.second;

		double lat = 1200 * (x - latMin) / (latMax - latMin);
		double lon =1200 * (y - longMin)/ (longMax - longMin);

		gv->addNode(id, lat, lon);
	}

	//--------------------------------------------- arestas.txt----------------------------------------------//
	inFile.open("road.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	int idAresta;
	string temp;

	while(std::getline(inFile, line))
	{
		stringstream linestream(line);
		string data;
		string temp;

		linestream >> idAresta;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> temp;

		if(temp == "True")
			twoWays.push_back(idAresta);
	}
	inFile.close();

	//--------------------------------------------- subroads.txt----------------------------------------------//
	inFile.open("subRoad.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	int newIdAresta = 0;
	idAresta=0;
	int newIdNoOrigem, newIdNoDestino;
	int idNoOrigem;
	int idNoDestino;

	while(std::getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;

		for(unsigned int i = 0; i < vertexIndex.size(); i++)
		{
			if(vertexIndex[i].second == idNoOrigem)
				newIdNoOrigem = vertexIndex[i].first;
			else
				if(vertexIndex[i].second == idNoDestino)
					newIdNoDestino = vertexIndex[i].first;
		}


		Vertex<Morada>* vSource = mapa.getVertexByID(newIdNoOrigem);
		Vertex<Morada>* vDest = mapa.getVertexByID(newIdNoDestino);
		double weight =  haversineAlgorith(vSource->getInfo().getX(), vSource->getInfo().getY(), vDest->getInfo().getX(), vDest->getInfo().getY());
		if(vSource->getInfo() == vDest->getInfo())
			continue;
		else{
			if(vSource != NULL && vDest != NULL){
				stringstream label;
				label << weight;
				mapa.addEdge(vSource->getInfo(), vDest->getInfo(), weight, newIdAresta);
				gv->addEdge(newIdAresta, newIdNoOrigem, newIdNoDestino, EdgeType::DIRECTED);
				gv->setEdgeLabel(newIdAresta,label.str());
				newIdAresta++;
				gv->addEdge(newIdAresta, newIdNoDestino, newIdNoOrigem, EdgeType::DIRECTED);
				gv->setEdgeLabel(newIdAresta,label.str());
				mapa.addEdge(vDest->getInfo(),vSource->getInfo(), weight, newIdAresta);
				newIdAresta++;


			}
		}
	}

	inFile.close();

	//inicializa o boleano isPI( é ponto de interesse) a falso
	mapa.resetIsPI();
	//display(gv);
	//gv->rearrange();
	return;
}
Graph<Morada> Mapa::getMapa(){
	return mapa;
}
void Mapa::cleanMapa(GraphViewer *gv)
{
	for(int i = 0; i < mapa.getNumVertex(); i++)
		gv->setVertexColor(mapa.getVertexByID(i)->getInfo().getID() , "pink");
}

// FUNÇÃO QUE TRAÇA O CAMINHO DE POINTS -> CHAMADA EM Mapa()
void Mapa::displayPath(GraphViewer *gv, vector<Morada> points, int condition){

	cleanMapa(gv);
	Sleep(2000);

	for(size_t l = 0; l < points.size(); l++)
	{
		Vertex<Morada> * v = mapa.getVertexByID(points[l].getID());
		if(v == NULL)
			return;
		if(condition == 0) // normal
			if(l == points.size()-1)
				gv->setVertexColor(points[l].getID(), "red");
			else
				gv->setVertexColor(points[l].getID(), "magenta");

		if(condition == 1) // inverso
			if(l == 0)
				gv->setVertexColor(points[l].getID(), "red");
			else
				gv->setVertexColor(points[l].getID(), "magenta");

		if(condition == 2) // só pontos de recolha

			gv->setVertexColor(points[l].getID(), "magenta");
		if(condition == 3) // só escolas
			gv->setVertexColor(points[l].getID(), "red");

		gv->rearrange();
		Sleep(500);
	}

}

// FUNÇÃO SÓ PARA TESTE
void Mapa::displayMapa(vector<Morada> points){
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);
	gv->defineEdgeColor("black");
	gv->defineVertexColor("pink");

	// Faz o mapa sem nada

	int k = 0;
	for(int i = 0; i < mapa.getNumVertex(); i++){
		Vertex<Morada> * v = mapa.getVertexByID(i);
		if(v->getInfo() == points.at(0) || v->getInfo() == points.at(points.size()-1)) //destino e inicio
			gv->setVertexColor(v->getInfo().getID(), "yellow");

		gv->addNode(i,v->getInfo().getX(),v->getInfo().getY());
		for(int j = 0; j < v->getNumAdjacents(); j++){
			int dest = v->getAdjacentNumber(j).getDest()->getInfo().getID();
			gv->addEdge(k,v->getInfo().getID(),dest, EdgeType::DIRECTED);
			stringstream label;
			label << v->getAdjacentNumber(j).getWeight();
			gv->setEdgeLabel(k,label.str());
			k++;
		}
	}

	for(size_t l = 0; l < points.size(); l++)
	{
		for(int i = 0; i < mapa.getNumVertex(); i++)
		{
			Vertex<Morada> * v = mapa.getVertexByID(i);
			if(v->getInfo().getID() == points[l].getID())
			{
				gv->setVertexColor(v->getInfo().getID(), "magenta");
				gv->rearrange();

				Sleep(1000);
			}
		}
	}

	gv->rearrange();
}

bool Mapa::setPontoInteresse(Morada m,bool b){

	Vertex<Morada> *v = mapa.getVertex(m);

	if(v == NULL)
		mapa.addVertex(m);

	//verificar se o ponto é valido (ou seja verificando as tabelas de floyd-warshall, este ponto é atingivel e intermediario)
	if(mapa.hasIncoming(v) && mapa.hasOutgoing(v)){
		v->setIsPI(b);
		return true;
	}
	return false;

}

bool Mapa::isPontoInteresse(Morada m){
	Vertex<Morada> *v = mapa.getVertex(m);
	return v->getIsPI();
}

int Mapa::displayPontos() const{
	for (int var = 0; var < mapa.getNumVertex(); ++var) {
		cout << mapa.getVertexSet()[var]->getInfo() << endl;
	}
	return 0;
}

Morada Mapa::getPonto(int id){
	for (int var = 0; var < mapa.getNumVertex(); ++var) {
		if(mapa.getVertexSet()[var]->getInfo().getID() == id)
			return mapa.getVertexSet()[var]->getInfo();
	}
	Morada m;
	m.setID(-1);
	return m;
}

Vertex<Morada> * Mapa::getPontoVertex(int id){

	Vertex<Morada> * v;
	for (int var = 0; var < mapa.getNumVertex(); ++var) {
		if(mapa.getVertexSet()[var]->getInfo().getID() == id)
			return v = mapa.getVertexSet()[var];
	}

	return v;
}

void Mapa::makefloydWarshallShortestPath(){
	mapa.floydWarshallShortestPath(); //crias as tabelas do path e dist entre todos os pontos
}

vector<Morada> Mapa::getInterestPoints() const{
	vector<Morada> res;
	for (int i = 0; i < mapa.getNumVertex(); ++i) {
		if(mapa.getVertexSet()[i]->getIsPI()){
			res.push_back(mapa.getVertexSet().at(i)->getInfo());
		}
	}
	return res;
}

void Mapa::setPontoProcessado(Morada ponto, bool estado){
	mapa.setProcessing(ponto,estado);
}

bool Mapa::getPontoProcessado(Morada ponto){
	return mapa.getProcessing(ponto);
}

int Mapa::getMinDistBetweenPoints(int pi, vector<Morada> points){
	return mapa.getMinDistAndPath(pi,points);
}

/**
 * Funcao que recebe como parametros os pontos por onde o grafo deve passar (ordenados) e faz o caminho até esse pontos
 */
vector<Morada> Mapa::makePath(vector<Morada> points){

	vector<Morada> path;

	for(size_t i = 0; i < points.size()-1; i++){
		vector<Morada> temp = mapa.getfloydWarshallPath(points.at(i), points.at(i+1));

		if(i == 0)
			path.push_back(temp.at(0));

		for(size_t k = 0; k < temp.size(); k++){
			if(k != 0)
				path.push_back(temp.at(k));
		}
	}
	return path;
}
