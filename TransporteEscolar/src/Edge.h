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
	bool isBlocked;
	string name;
public:
	Edge(Vertex<T> *d, double w, int id, string n);
	friend class Graph<T>;
	friend class Vertex<T>;
	Vertex<T> *getDest() const;
	double getWeight() const;
	int getID() const;
	bool getIsBlocked() const;
	string getName() const {return name;}
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, int id, string n): dest(d), weight(w), idEdge(id), isBlocked(false), name(n){}

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
template <class T>
bool Edge<T>::getIsBlocked() const{
	return isBlocked;
}

#endif /* SRC_EDGE_H_ */
