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

/*
Mapa::Mapa(){
	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	string line;

	int idNo=0;
	int x=0;
	int y=0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string	data;

		linestream >> idNo;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> x;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> y;
		Morada m = Morada(x,y,idNo);
		mapa.addVertex(m);
	}

	inFile.close();

	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	int idAresta=0;
	int idNoOrigem=0;
	int idNoDestino=0;
	int peso = 0;

	while(std::getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> peso;

		Vertex<Morada>* vSource = mapa.getVertexByID(idNoOrigem);
		Vertex<Morada>* vDest = mapa.getVertexByID(idNoDestino);

		mapa.addEdge(vSource->getInfo(), vDest->getInfo(), peso,1);
		mapa.addEdge(vDest->getInfo(), vSource->getInfo(), peso,1);
	}
	inFile.close();

	//inicializa o boleano isPI( é ponto de interesse) a falso
	mapa.resetIsPI();
}*/
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

Mapa::Mapa(){

	//openstreetmaps.org

	vector<int > twoWays; //se uma aresta estiver neste vértice significa que a sua rua é bidirecional

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("LisboaNodes.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	string line;

	int idNo=0;
	double x=0;
	double y=0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string	data;

		linestream >> idNo;
		getline(linestream, data, ';');  // discard lat in º
		getline(linestream, data, ';');  // discard long in º
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> x;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> y;
		Morada m = Morada(x,y,idNo);
		mapa.addVertex(m);
	}

	inFile.close();

	//Ler o ficheiro arestas.txt

	inFile.open("LisboaRoads.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	int idAresta=0;
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

	//Ler o ficheiro SubRoads.txt
	inFile.open("LisboaSubRoads.txt");

	if (!inFile)
		cerr << "Unable to open file datafile.txt";

	idAresta=0;
	int idNoOrigem=0;
	int idNoDestino=0;

	while(std::getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;

		Vertex<Morada>* vSource = mapa.getVertexByID(idNoOrigem);
		Vertex<Morada>* vDest = mapa.getVertexByID(idNoDestino);
		double weight =  haversineAlgorith(vSource->getInfo().getX(), vSource->getInfo().getY(), vDest->getInfo().getX(), vDest->getInfo().getY());
		if(vSource == vDest)
			continue;
		else{
			if(vSource != NULL && vDest != NULL){
				mapa.addEdge(vSource->getInfo(), vDest->getInfo(), weight, idAresta);
				for(size_t i = 0; i < twoWays.size(); i++)
					if(twoWays.at(i) == idAresta){	//esta aresta está nos vetores de arestas bidirecionais
						mapa.addEdge(vDest->getInfo(),vSource->getInfo(), weight, idAresta);
					}
			}
		}
	}

	inFile.close();

	//inicializa o boleano isPI( é ponto de interesse) a falso
	mapa.resetIsPI();
}
/*
void Mapa::displayMapa(vector<Morada> points){
	GraphViewer *gv = new GraphViewer(1200, 1200, false);

	gv->createWindow(1200, 1200);
	gv->defineEdgeColor("black");
	gv->defineVertexColor("pink");

	// Faz o mapa sem nada

	vector<Vertex<Morada> *> allVertex = mapa.getVertexSet();
	for(int i = 0; i < mapa.getNumVertex(); i++){
		Vertex<Morada> * v = allVertex.at(i);

		gv->addNode(v->getInfo().getID(),v->getInfo().getX(),v->getInfo().getY());
		//--------------------------------------------------------------------------//
		for(int j = 0; j < v->getNumAdjacents(); j++){
			int dest = v->getAdjacentNumber(j).getDest()->getInfo().getID();
			int k = v->getAdjacentNumber(j).getID();
			gv->addEdge(k,v->getInfo().getID(),dest, EdgeType::DIRECTED);
			stringstream label;
			label << v->getAdjacentNumber(j).getWeight();
			gv->setEdgeLabel(k,label.str());
			k++;
		}

		//--------------------------------------------------------------------------//
	}

	// Começa a animação


	for(int l = 0; l < points.size(); l++)
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
 */

void Mapa::display(){
	GraphViewer *gv = new GraphViewer(4000, 4000, false);

	gv->createWindow(4000, 4000);
	gv->defineEdgeColor("black");
	gv->defineVertexColor("pink");

	vector<Vertex<Morada> * > m = mapa.getVertexSet();
	int offset =0;
	for(int i = 0; i < m.size(); i++){

		Vertex<Morada> * v = m.at(i);
		//cout << "nº "<< i << " x " <<v->getInfo().getX() << " y " << v->getInfo().getY() << endl;
		gv->addNode(v->getInfo().getID(),v->getInfo().getX()+ 100 + offset,v->getInfo().getY() + 100 + offset/2) ;

		for(int j = 0; j < v->getNumAdjacents(); j++){

			//cout << "j " << j << endl;
			Edge<Morada> e = v->getAdjacentNumber(j);
			int edgeID = e.getID();
			int dest = e.getDest()->getInfo().getID();
			int src = v->getInfo().getID();

			gv->addEdge(edgeID,src,dest, EdgeType::DIRECTED);
			stringstream label;
			label << v->getAdjacentNumber(j).getWeight();
			gv->setEdgeLabel(edgeID,label.str());

		}
		if(i%2 == 0)
			offset += 100;
		else
			offset -= 100;

		offset += 3;

	}
}

void Mapa::displayMapa(vector<Morada> points){
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);
	gv->defineEdgeColor("black");
	gv->defineVertexColor("pink");

	// Faz o mapa sem nada

	int k = 0;
	for(int i = 0; i < mapa.getNumVertex(); i++){
		Vertex<Morada> * v = mapa.getVertexByID(i);
		/*if(v->getIsPI())
			gv->setVertexColor(v->getInfo().getID(), "red");*/
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

	/*	// Começa a animação
//----------------------------------------------------------------------------//
	k = 0;
	for(int i = 0; i < mapa.getNumVertex(); i++)
	{
			Vertex<Morada> * v = mapa.getVertexByID(i);
			if(isPontoInteresse(v->getInfo()))
			{
				for(int j = 0; j < v->getNumAdjacents(); j++){
					int dest = v->getAdjacentNumber(j).getDest()->getInfo().getID();
					cout << "i " << i << " j " << j <<" dest " << dest << " k " << k << endl;;
					Vertex<Morada> * destino = mapa.getVertexByID(dest);
					if(isPontoInteresse(v->getAdjacentNumber(j).getDest()->getInfo()))
					{
						cout << "vou colocar" << endl;
						gv->setEdgeColor(k,"magenta");
						gv->rearrange();
					}

					gv->setVertexColor(v->getInfo().getID(), "magenta");
					gv->rearrange();

					Sleep(1000);
					k++;
				}
			}
			else
				for(int j = 0; j < v->getNumAdjacents(); j++){k++;}
		}
//----------------------------------------------------------------------------//
	 */

	Sleep(3000);

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


	/*
//----------------------------------------------------------------------------//
	for(int i = 0; i < mapa.getNumVertex(); i++){
		Vertex<Morada> * v = mapa.getVertexByID(i);
		if(isPontoInteresse(v->getInfo()))
			gv->setVertexColor(v->getInfo().getID(), "magenta");

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
//----------------------------------------------------------------------------//
	 * */
	gv->rearrange();
}

void Mapa::setPontoInteresse(Morada m,bool b){

	Vertex<Morada> *v = mapa.getVertex(m);
	v->setIsPI(b);

	if(v == NULL)
		mapa.addVertex(m);
}

bool Mapa::isPontoInteresse(Morada m){
	Vertex<Morada> *v = mapa.getVertex(m);
	return v->getIsPI();
}

/*int Mapa::isPonto(Morada m) const{
	for (int var = 0; var < mapa.getNumVertex(); ++var) {
		if(mapa.getVertexSet()[var]->getInfo().getX() == m.getX() &&
				mapa.getVertexSet()[var]->getInfo().getY() == m.getY())
			return mapa.getVertexSet()[var]->getInfo().getID();
	}
	return -1;
}*/

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
	mapa.floydWarshallShortestPath();
}

vector<Morada> Mapa::shortestPath(vector<Morada> points){
	mapa.floydWarshallShortestPath();
	vector<Morada> res = mapa.getfloydWarshallPathWithIP(points);

	if(res.size() == 1){ // e retornado um vetor vazio
		cout << "ATENCAO! O GRAFO NAO PERMITE CHEGAR AO PONTO " << res.at(0).getID() << endl ; //isto tem de ir para o main mais tarde
	}else
		return res;
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

int Mapa::getMinDistBetweenPoints(int pi, vector<Morada> points, vector<Morada> &res){
	return mapa.getMinDistAndPath(pi,points,res);
}
