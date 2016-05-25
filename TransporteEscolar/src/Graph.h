/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.h"
#include "Edge.h"
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>

#include "graphviewer.h"


const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = 10000 ; //INT_MAX compor isto

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

/*
 * GRAPH
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	vector<Edge<T> *> edgeSet; // criado para o trabalho
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);
	int W[1000][1000];
	Vertex<T> * P[1000][1000];

public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w, int id, string n);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	Vertex<T>* getVertex(const T &v) const;
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	int edgeCost(int i, int j);
	Vertex<T>* getVertexByID(const int id) const;
	void resetIsPI();
	void resetIsSchool();
	void setProcessing(T info, bool estado);
	bool getProcessing(T info);
	int getMinDistAndPath(int pi, vector<T> points);
	bool edgeExists(Edge<T>* e);
	bool hasIncoming(Vertex<T> *v);
	bool hasOutgoing(Vertex<T> *v);
	void setEdgeBlocked(int idEdge, bool state);
	vector<Edge<T> > getBlockedEdges() const;
};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::edgeExists(Edge<T>* e)
{
	for(int i = 0; i < edgeSet.size(); i++)
		if(e->getID() == edgeSet[i]->getID())
			return true;

	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, int id, string n) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	//Edge<T>* e = new Edge<T>(vD, w, id);
	//if ((found!=2)||(edgeExists(e))) return false;
	if(found != 2)
		return false;
	vD->indegree++;
	vS->addEdge(vD,w,id, n);
	//edgeSet.push_back(e);

	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){
	//so serve para interpretar a matriz P[i][j]

	vector<T> res;
	vector<T> invert;
	Vertex<T> *v = P[origin.getID()][dest.getID()];

	res.push_back(dest);
	while(true){
		if(v->getInfo().getID() == origin.getID())
			break;

		else{
			res.push_back(v->getInfo());
			v = P[origin.getID()][v->getInfo().getID()];
		}
	}
	res.push_back(origin);

	//inverter res
	for(int j = res.size()-1; j >= 0; j--)
		invert.push_back(res.at(j));

	return invert;
}

template<class T>
int Graph<T>::edgeCost(int i, int j){
	Vertex<T>* vi = vertexSet[i];
	Vertex<T>* vf = vertexSet[j];

	for(size_t i = 0; i < vi->adj.size(); i++)
		if(vi->adj[i].dest == vf && !vi->adj[i].isBlocked) //a aresta não está bloqueada
			return vi->adj[i].weight;

	return 0;
}


/**
 * Preenche W[i][j] e P[i][j]
 */
template<class T>
void Graph<T>::floydWarshallShortestPath(){

	//inicializacao
	for(unsigned int i = 0 ; i < vertexSet.size(); i++){
		for(unsigned int j = 0 ; j < vertexSet.size() ; j++){
			if( i == j){
				P[i][j] = NULL;
				W[i][j] = 0;
			}else{
				int peso = edgeCost(i,j);
				if(peso > 0){ // existe ligacao direta
					W[i][j] = peso;
					P[i][j] = vertexSet[i];
				}
				else{
					W[i][j] = INT_INFINITY;
					P[i][j] = NULL;
				}
			}
		}
	}

	//forumula : D[i][j]^k = min( D[i][j]^(k-1) , D[i][k]^(k-1) + D[k][j]^(k-1 )
	for(size_t k = 0; k < vertexSet.size(); k++)
		for(size_t i = 0; i < vertexSet.size(); i++)
			for(size_t j = 0; j < vertexSet.size(); j++){
				if((W[i][j] == INT_INFINITY && W[i][k] != INT_INFINITY && W[k][j] != INT_INFINITY )){
					W[i][j] = W[i][k] + W[k][j];
					P[i][j] = P[k][j];
				}if(W[i][j] > W[i][k] + W[k][j] && (W[i][j] != INT_INFINITY && W[i][k] != INT_INFINITY && W[k][j] != INT_INFINITY )){
					W[i][j] = W[i][k] + W[k][j];
					P[i][j] = P[k][j];
				}
			}
}

template<class T>
Vertex<T>* Graph<T>::getVertexByID(const int id) const{
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info.getID() == id)
			return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIsPI(){
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		vertexSet[i]->isPI = false;
}

template<class T>
void Graph<T>::resetIsSchool(){
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		vertexSet[i]->isSchool = false;
}

template<class T>
void Graph<T>::setProcessing(T info, bool estado){
	for(size_t j = 0; j < vertexSet.size(); j++)
		if(vertexSet.at(j)->getInfo() == info){
			vertexSet.at(j)->processing = estado;
			break;
		}
}

template<class T>
bool Graph<T>::getProcessing(T info){
	Vertex<T> *v = getVertex(info);
	return v->processing;
}

/**
 * funcao que recebe uma morada, e um vetor de moradas e retorna o indice do vetor com a morada mais proxima.
 * também recebe um vetor que guarda o caminho entre esses 2 pontos.
 */
template<class T>
int Graph<T>::getMinDistAndPath(int pi, vector<T> points){

	//ver qual dos PI esta mais proximo do 'info'
	int dist = INT_INFINITY;
	int min = -1; //pi mais proximo
	Vertex<T> *vInfo = getVertex(points.at(pi));

	for(size_t i = 0; i < points.size(); i++){
		Vertex<T> *v = getVertex(points.at(i)); // vertice correpondente à morada
		//a pesquisa na tablela é feita pelo id de cada n

		if(W[points.at(pi).getID()][points.at(i).getID()] < dist && !(vInfo == v) && v->processing == false){
			dist = W[points.at(pi).getID()][points.at(i).getID()];
			min = i;
		}
	}

	if(dist == INT_INFINITY)
		return pi; //siginifica que todos os pontos estão processados OU houve um erro

	return min;
}

//verifica se um vertice é alcancavel
template<class T>
bool Graph<T>::hasIncoming(Vertex<T> *v){
	int id = v->getInfo().getID();

	for(size_t i = 0; i < vertexSet.size(); i++)
		if(id != i)
			if(W[i][id] != INT_INFINITY)
				return true;
	return false;
}

//verifica se um grafo é interemediario
template<class T>
bool Graph<T>::hasOutgoing(Vertex<T> *v){
	int id = v->getInfo().getID();

	for(size_t i = 0; i < vertexSet.size(); i++)
		if(id != i)
			if(W[i][id] != INT_INFINITY)
				return true;
	return false;
}

template<class T>
void Graph<T>::setEdgeBlocked(int idEdge, bool state){

	for(size_t i = 0; i < vertexSet.size(); i++){
		vector<Edge<T> > temp = vertexSet.at(i)->adj;
		for(size_t j = 0; j < temp.size(); j++)
			if(temp.at(j).idEdge == idEdge){
				vertexSet.at(i)->adj.at(j).isBlocked = state;
				break;
			}
	}
}

template<class T>
vector<Edge<T> > Graph<T>::getBlockedEdges() const{
	vector<Edge<T> > res;

	for(size_t i = 0; i < vertexSet.size(); i++){
		vector<Edge<T> > temp = vertexSet.at(i)->adj;
		for(size_t j = 0; j < temp.size(); j++)
			if(temp.at(j).isBlocked)
				res.push_back(temp.at(j));
	}
	return res;
}



#endif /* GRAPH_H_ */
