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

		mapa.addEdge(vSource->getInfo(), vDest->getInfo(), peso);
	}
	inFile.close();

	//inicializa o boleano isPI( é ponto de interesse) a falso
	mapa.resetIsPI();
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
		if(i==0)
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

	// Começa a animação
 /*
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

	*/
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






/*
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
	}*/

	gv->rearrange();
}

void Mapa::setPontoInteresse(Morada m){

	Vertex<Morada> *v = mapa.getVertex(m);
	v->setIsPI(true);

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


vector<Morada> Mapa::shortestPath(vector<Morada> points){
	mapa.floydWarshallShortestPath();
	vector<Morada> res = mapa.getfloydWarshallPathWithIP(points);

	if(res.size() == 1){ // e retornado um vetor vazio
		cout << "ATENCAO! O GRAFO NAO PERMITE CHEGAR AO PONTO " << res.at(0).getID() << endl ; //isto tem de ir para o main mais tarde
	}else
		return res;
}
