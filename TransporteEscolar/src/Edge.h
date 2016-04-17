/*
 * Edge.h
 *
 *  Created on: 06/04/2016
 *      Author: Inês Gomes
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	int idEdge;
public:
	Edge(Vertex<T> *d, double w, int id);
	friend class Graph<T>;
	friend class Vertex<T>;

	//=================ACRESCENTADOS PARA O TRABALHO=======================//
	Vertex<T> *getDest() const;
	double getWeight() const;
	int getID() const;

};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, int id): dest(d), weight(w), idEdge(id){}

//=================ACRESCENTADOS PARA O TRABALHO=======================//
template <class T>
Vertex<T> *Edge<T>::getDest() const{
	return dest;
}

template <class T>
double Edge<T>::getWeight() const{
	return weight;
}

template <class T>
int Edge<T>::getID() const{
	return idEdge;
}


#endif /* SRC_EDGE_H_ */
