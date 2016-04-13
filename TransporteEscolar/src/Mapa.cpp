#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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

void Mapa::displayMapa(){
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("black");
	gv->defineVertexColor("pink");

	int k = 0;

	for(int i = 0; i < mapa.getNumVertex(); i++){
		Vertex<Morada> * v = mapa.getVertexByID(i);
		if(isPontoInteresse(v->getInfo()))
			gv->setVertexColor(v->getInfo().getID(), "red");

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
