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

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = 10000; //INT_MAX; compor isto

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
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	int W[1000][1000];
	Vertex<T> * P[1000][1000];

public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w, int id);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	int edgeCost(int i, int j);

	//=================== CRIADOS PARA O TRABALHO ===============//
	vector<T> getfloydWarshallPathWithIP(vector<T> points);
	Vertex<T>* getVertexByID(const int id) const;
	void resetIsPI();
	bool getfloydWarshallPathWithIPAux(vector<T> points, int pi, vector<T> &res);
	void setProcessing(T info, bool estado);
	bool getProcessing(T info);
	int getMinDistAndPath(int pi, vector<T> points);
	bool edgeExists(Edge<T>* e);
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
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
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
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, int id) {
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
	vS->addEdge(vD,w,id);
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
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false ){
			dfs(it->dest, res);
		}
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}


template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfsVisit(*it);
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
		if ( it->dest->visited == false ){
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vector com o resultado da ordenacao
	vector<T> res;

	//verificar se é um DAG
	if( getNumCycles() > 0 ) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while( !sources.empty() ) {
		q.push( sources.back() );
		sources.pop_back();
	}

	//processar fontes
	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if( v->adj[i].dest->indegree == 0) q.push( v->adj[i].dest );
		}
	}

	//testar se o procedimento foi bem sucedido
	if ( res.size() != vertexSet.size() ) {
		while( !res.empty() ) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}



template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	//cout << v->info << " ";
	buffer.push_front(v->info);
	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<T> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if( w->dist == INT_INFINITY ) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}


/**
 * este método apenas difere do unweightedShortestPath, porque a soma será com o peso
 */
template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s){

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front();
		q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			int sum = v->dist + v->adj[i].weight;
			if( (w->dist == INT_INFINITY) || (sum < w->dist)) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s){

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector<Vertex<T>*> vec;
	vec.push_back(v);

	while( !vec.empty() ) {
		v = vec.at(0);
		vec.erase(vec.begin()+0); //elimina o primeiro elmento da heap
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			int sum = v->dist + v->adj[i].weight;
			if( (w->dist == INT_INFINITY) || (sum < w->dist)) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				vec.push_back(w);
				w->processing = true;
			}
			make_heap(vec.begin(),vec.end(),vertex_greater_than<int>()); //ordenar o vetor como se fosse uma heap
		}
	}
}


template<class T>
bool Graph<T>::getfloydWarshallPathWithIPAux(vector<T> points, int pi, vector<T> &res){

	bool path = false;
	vector<T> nop; //conjunto de vertices que não têm solucao

	while(!path){
		//ver qual dos PI esta mais proximo da origem (nao inclui o primeiro ponto e o ultimo)
		int dist = INT_INFINITY;
		int min = 0; //pi mais proximo

		for(size_t i = 1; i < points.size()-1; i++){
			Vertex<T> *v = getVertex(points.at(i)); // vertice correpondente à morada

			//se o vertice estiver neste vetor significa que o caminho por esse vetor é impossivel
			bool skip = false;
			for(size_t j = 0; j < nop.size(); j++)
				if(v->getInfo() == nop.at(j))
					skip = true;

			//a pesquisa na tablela é feita pelo id de cada nó
			if(W[points.at(pi).getID()][points.at(i).getID()] < dist && v->processing == false && !skip){
				dist = W[points.at(pi).getID()][points.at(i).getID()];
				min = i;
			}
		}

		//verifica a conectividade
		//para um grafo ser conexo as ligacoes entre os pontos de interesse têm de ser possiveis
		if(dist == INT_INFINITY){
			//verifica se só o destino é que ainda nao foi processado
			for(size_t j = 0; j < points.size()-1; j++){
				Vertex<T> *v1 = getVertex(points.at(j)); // vertice atual
				Vertex<T> *v2 = getVertex(points.at(pi)); // vertice que corresponde ao ponto de interesse em analise
				if(!(v1->processing) && !(v1 == v2))
					return false; //no caso em que um grafo não é conexo retornamos falso para escolher um novo caminho
			}

			//caso em que já percorreu todos os pontos de interesse
			min = points.size()-1; //destino
			if(P[points.at(pi).getID()][points.at(min).getID()] == NULL) //nao e possivel chegar a saida
				return false;
			path = true;
		}

		//coloca o min como processado
		setProcessing(points.at(min), true);

		//fazer o path até esse caminho
		vector<T> temp = getfloydWarshallPath(points.at(pi), points.at(min));
		for(size_t k = 0; k < temp.size(); k++)
			if(k != 0)
				res.push_back(temp.at(k));

		//significa que chegamos ao destino
		//condicao de terminacao
		if(path)
			return true;

		if(getfloydWarshallPathWithIPAux(points, min,res))
			return true;

		//elimina o caminho acrescentado
		for(size_t k = 0; k < temp.size()-1; k++)
			res.erase(res.end()-1);

		//retirar de processado o min
		setProcessing(points.at(min), false);

		//fazer outra vez o mesmo processo mas não pode ser igual a min
		nop.push_back(points.at(min));
	}
}

/**
 * recebe um vetor com os ponts de interess.
 * De seguidacalcula o caminho mais curto que passa nesses pontos.
 * O primeiro ponto de interesse é a origem e o ultimo o destino.
 */
template<class T>
vector<T> Graph<T>::getfloydWarshallPathWithIP(vector<T> points){

	vector<T> res; //vetor que guarda o path e será retornado
	vector<T> temp;

	//inicializa todos os vertices a falso (valor de processo)
	for(size_t j = 0; j < vertexSet.size(); j++)
		vertexSet.at(j)->processing = false;

	unsigned int pi = 0; //posicao do ponto de interesse atual no vetor points -> comeca na origem

	res.push_back(points.at(pi));
	setProcessing(points.at(pi), true);

	if(getfloydWarshallPathWithIPAux(points, pi,res))
		return res;
	else{
		cout << "O caminho não chega a todos os pontos de interesse\n"; //enviar por exemplo vetor vazio -> significa que é impossivel passar em todas as criancas
		return res;
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){
	//so serve para interpretar a matriz P[i][j]

	vector<T> res;
	vector<T> invert;
	Vertex<T> *v = P[origin.getID()][dest.getID()];

	res.push_back(dest);
	while(true){
		if(v->getInfo() == origin)
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

	for(size_t i = 0; i < vi->adj.size(); i++){
		if(vi->adj[i].dest == vf)
			return vi->adj[i].weight;
	}
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

//=================== CRIADOS PARA O TRABALHO ===============//
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

	floydWarshallShortestPath();

	//ver qual dos PI esta mais proximo do 'info'
	int dist = INT_INFINITY;
	int min = -1; //pi mais proximo
	Vertex<T> *vInfo = getVertex(points.at(pi));

	for(size_t i = 0; i < points.size(); i++){
		Vertex<T> *v = getVertex(points.at(i)); // vertice correpondente à morada
		//a pesquisa na tablela é feita pelo id de cada n

		if(W[points.at(pi).getID()][points.at(i).getID()] < dist && !(vInfo == v) && !(v->processing)){
			dist = W[points.at(pi).getID()][points.at(i).getID()];
			min = i;
		}
	}

	if(dist == INT_INFINITY)
		return pi; //siginifica que todos os pontos estão processados OU houve um erro

	return min;
}


#endif /* GRAPH_H_ */
