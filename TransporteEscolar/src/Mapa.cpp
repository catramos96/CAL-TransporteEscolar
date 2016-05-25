#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Mapa::Mapa(GraphViewer *gv){

	//openstreetmaps.org
	gv->defineVertexColor("pink");

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

		Morada m = Morada(x,y,newIdNo, "");
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
	int newIdAresta = 0;
	vector<pair<unsigned int, string> > edgeIndex;

	while(std::getline(inFile, line))
	{
		stringstream linestream;
		string data;
		string temp;
		string nome;

		linestream << line;
		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).

		nome = data;

		getline(linestream, data, ';');
		temp = data;

		pair<unsigned int, string> idPair;
		idPair.first = idAresta;
		idPair.second = nome;
		edgeIndex.push_back(idPair);
		newIdAresta++;

		if(temp == "True")
			twoWays.push_back(idAresta);
	}
	inFile.close();

	//--------------------------------------------- subroads.txt----------------------------------------------//
	inFile.open("subRoad.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	newIdAresta = 0;
	idAresta=0;
	int newIdNoOrigem, newIdNoDestino;
	int idNoOrigem;
	int idNoDestino;

	while(std::getline(inFile, line))
	{
		stringstream linestream(line);
		string data;
		string edgeLabel;

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

		for(unsigned int j = 0; j < edgeIndex.size(); j++)
		{
			if(idAresta == edgeIndex[j].first)
				edgeLabel = edgeIndex[j].second;
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
				mapa.addEdge(vSource->getInfo(), vDest->getInfo(), weight, newIdAresta, edgeLabel);
				gv->addEdge(newIdAresta, newIdNoOrigem, newIdNoDestino, EdgeType::DIRECTED);
				//gv->setEdgeLabel(newIdAresta,label.str());
				gv->setEdgeLabel(newIdAresta,edgeLabel);
				newIdAresta++;
				gv->addEdge(newIdAresta, newIdNoDestino, newIdNoOrigem, EdgeType::DIRECTED);
				//gv->setEdgeLabel(newIdAresta,label.str());
				//gv->setEdgeLabel(newIdAresta,edgeLabel);
				mapa.addEdge(vDest->getInfo(),vSource->getInfo(), weight, newIdAresta,edgeLabel);
				newIdAresta++;
			}
		}
	}

	inFile.close();

	for(unsigned int i = 0; i < mapa.getNumVertex(); i++)
	{
		string name = mapa.getVertexByID(i)->getAdjacentNumber(0).getName();
		Morada m = mapa.getVertexByID(i)->getInfo();
		m.setNome(name);
		mapa.getVertexByID(i)->setInfo(m);
	}

	//inicializa o boleano isPI( é ponto de interesse) e isSchool ( é uma escola) a falso
	mapa.resetIsPI();
	mapa.resetIsSchool();

	return;
}

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

Graph<Morada> Mapa::getMapa(){
	return mapa;
}

void Mapa::cleanMapa(GraphViewer *gv)
{
	for(int i = 0; i < mapa.getNumVertex(); i++)
		gv->setVertexColor(mapa.getVertexByID(i)->getInfo().getID() , "pink");
}

// FUNÇÃO QUE TRAÇA O CAMINHO DE POINTS -> CHAMADA EM Mapa()
void Mapa::displayPath(GraphViewer *gv, vector<Morada> points, bool makePath){

	cleanMapa(gv);
	Sleep(2000);

	vector<Vertex<Morada> *> allVertex = mapa.getVertexSet();
	vector<Edge<Morada> > adj;

	//pinta arestas bloqueadas a vermelho
	for(size_t i = 0; i < allVertex.size(); i++){
		vector<Edge<Morada> > adj = allVertex.at(i)->getAdjacents();
		for(size_t j = 0; j < adj.size(); j++)
			if(adj.at(j).getIsBlocked())
				gv->setEdgeColor(adj.at(j).getID(),"red");
	}

	for(size_t l = 0; l < points.size(); l++)
	{
		Vertex<Morada> * v = mapa.getVertexByID(points[l].getID());
		if(v == NULL)
			return;

		if(v->getIsSchool())
			gv->setVertexColor(points[l].getID(), "red");
		else if(v->getIsPI())
			gv->setVertexColor(points[l].getID(), "blue");
		else
			gv->setVertexColor(points[l].getID(), "magenta");

		gv->rearrange();

		if(makePath)
			Sleep(500);
	}

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

//lê a informacao que está no no grafo e cria um apontador
Morada *Mapa::getPonto(int id){
	Morada m;
	bool found = false;
	for (int var = 0; var < mapa.getNumVertex(); ++var) {
		if(mapa.getVertexSet()[var]->getInfo().getID() == id){
			m = mapa.getVertexSet()[var]->getInfo();
			found = true;
			break;
		}
	}
	if(!found)
		m.setID(-1);

	Morada *enviar = new Morada(m.getX(), m.getY(), m.getID(), m.getNome());

	return enviar;
}

Vertex<Morada> * Mapa::getPontoVertex(int id){

	Vertex<Morada> * v = mapa.getVertexByID(id);
/*	for (int var = 0; var < mapa.getNumVertex(); ++var) {
		if(mapa.getVertexSet()[var]->getInfo().getID() == id)
			return v = mapa.getVertexSet()[var];
	}
*/
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

void Mapa::setBlockedEdge(int edgeId, bool state){
	mapa.setEdgeBlocked(edgeId,state);
}

void Mapa::displayBlockedEdges(){
	vector<Edge<Morada> > temp = mapa.getBlockedEdges();

	for(size_t i = 0; i < temp.size(); i++)
		cout << temp.at(i).getID()<< endl;
}
