#include "Empresa.h"
#include <sstream>
#include <fstream>
#include <string.h>
#include "Excecoes.h"
#include <algorithm>

using namespace std;

/*
 * Construtor da classe Empresa.
 * @param nome Nome da empresa.
 * @param endereco Apontador para a morada do empresa.
 */
Empresa::Empresa(){
	initialization();
}

/**
 * Método que retorna o nome da empresa
 * @return nome da empresa.
 */
string Empresa::getNome() const {return nome;}

/**
 * Metodo que retorna a morada da empresa em forma de apontador.
 * @return morada da empresa
 */
Morada* Empresa::getEndereco() const {return endereco;}

/**
 * Metodo que altera o boleano que indica se uma empresa é escola ou não
 * @param b Valor do boleano.
 */
void Empresa::setIsEscola(bool b){ isEscola =b; }

/**
 * Metodo que retorna o boleano que indica se a empresa é uma escola
 * return boleano true ou false consoante e ou nao uma escola
 */
bool Empresa::getIsEscola() const{ return isEscola; }

/**
 * Metodo que retorna um vetor de apontadores com as escolas de todos os clientes.
 * @return Vetor de apontadores para moradas de escolas.
 */
vector<Morada *> Empresa::getEscolas() const{ return escolas; }

/**
 * Metodo que retorna o mapa associado a esta empresa.
 * @return objeto do tipo Mapa
 */
Mapa* Empresa::getMapa() const {return mapa;}

/**
 * Metodo que permite alterar o nome da empresa.
 * @param nome Novo nome.
 */
void Empresa::setNome(string nome) {this->nome = nome;}

/**
 * Metodo que permite alterar a morada da empresa.
 * @param endereco Apontador para a nova morada da empresa.
 */
void Empresa::setEndereco(Morada *endereco) {this->endereco = endereco;}

/**
 * Metodo que retorna todos os clientes daquela empresa que pertencem a escola passada como arguemto
 * @param escola Apontador para a morada da escola.
 * @return todos os clintes da escola que tem como morada 'escola'
 */
vector<Cliente *> Empresa::getClientesEscola(Morada *escola) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
	vector<Cliente *>::const_iterator itf = clientes.end();
	vector<Cliente *> res;
	while(itb != itf){
		if(*(*itb)->getEscola() == *escola)
			res.push_back(*itb);
		itb++;
	}
	return res;
}

/**
 * Metodo que retorna todos os clientes que pertencem ao ponto de recolha 'ponto'.
 * @param ponto Morada do ponto de recolha.
 * @return Conjunto de clientes que costumam apanhar o autocarro nesse ponto de recolha
 */
vector<Cliente *> Empresa::getClientesPontoRecolha(Morada * ponto) const{
	vector<Cliente *>::const_iterator itb = clientes.begin();
	vector<Cliente *>::const_iterator itf = clientes.end();
	vector<Cliente *> c;
	if(mapa->isPontoInteresse(*ponto) == false)
		throw PontoRecolhaInvalido(*ponto);
	while(itb != itf){
		if(*(*itb)->getResidencia() == *ponto)
			c.push_back(*itb);
		itb++;
	}
	return c;
}

/**
 * Metodo que muda a residencia dos clientes com id para o ponto de recolha mais próximo.
 * @param id do cliente
 */
void Empresa::setClientesPI(int id){
	vector<Cliente *> mudar_cli;
	//Seleccionar os clientes com a residencia com o mesmo id
	for (size_t i = 0; i < clientes.size(); ++i) {
		if(clientes[i]->getResidencia()->getID() == id)
			mudar_cli.push_back(clientes[i]);
	}
	//ir buscar o ponto de recolha mais proximo a id
	vector<Morada > pontosRecolha = mapa->getInterestPoints();

	int indice1 = -1,indice2 = -1;
	//procurar o indice do ponto de recolha com id
	for (size_t i = 0; i < pontosRecolha.size(); ++i) {
		if(pontosRecolha[i].getID() == id)
			indice1 = i;
	}

	if(indice1 == -1){
		cout << "Indice Invalido" << endl;
		throw VoltarAtras();
	}
	indice2 = mapa->getMinDistBetweenPoints(indice1,pontosRecolha);

	if(indice1 == indice2 || indice2 == -1)
		throw PontoRecolhaInvalido(pontosRecolha[indice1]);

	//substituir clientes para o ponto de recolha de indice2 em pontosRecolha

	//fazer uma fun��o que retorna o nome da primeira aresta que sai de um certo no

	Morada *m = new Morada(getEndereco()->getX(),getEndereco()->getY(),pontosRecolha[indice2].getID(),pontosRecolha[indice2].getNome());
	for (size_t i = 0; i < mudar_cli.size(); ++i) {
		mudar_cli[i]->setNovaResidencia(m);
	}
}

/**
 * Metodo que adiciona um novo veiculo a frota da empresa.
 * @param veiculo Apontador para o veiculo que sera adicionado.
 * @return True ou false consoante é ou não possivel adicionar o transporte a frota.
 */
bool Empresa::addTransporte(Veiculo * veiculo)
{
	if(veiculo->getNumLugares() <= 0)
		return false;
	for(unsigned int i = 0; i < transportes.size(); i++){
		if((*veiculo) == (*transportes[i])){
			return false;
		}
	}
	transportes.push_back(veiculo);
	return true;
}

/**
 * Metodo que adiciona um cliente ao vetor de clientes da empresa.
 * É necessario verificar se ainda existem lugares livres no total da frota, e se a crianca já existe no vetor de clientes.
 * @param cliente Cliente a ser introduzido.
 * @return True ou false consoante é ou nao possivel adicionar o cliente.
 */
bool Empresa::addCliente(Cliente *cliente)
{
	Cliente::id--; //para o caso de dar throw
	//veiculos insuficientes2
	unsigned int lugares = 0;
	for (size_t i = 0; i < transportes.size(); ++i) {
		lugares += transportes[i]->getNumLugares();
	}

	if(lugares < clientes.size())
		throw VeiculosInsuficientes();
	/*
	//residencia = escola
	if(cliente->getEscola()->getID() == cliente->getResidencia()->getID())
		throw ResidenciaInvalida(*cliente->getResidencia());

	//cliente ja existe, id = ou residencia =
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(*cliente == *clientes[i])
			return false;

	//residencia = escola(Empresa->escolas)
	for (size_t j = 0; j < escolas.size(); ++j)
		if(*cliente->getResidencia() == *escolas[j])
			return false;

	changeNumCriancas(*cliente->getResidencia(),1);	//mudar isto
	 */
	clientes.push_back(cliente);
	addEscola(cliente->getEscola());
	Cliente::id++;
	return true;
}

/**
 * Metodo que adiciona uma escola à base de dados de escolas da empresa.
 * @param e Escola a ser adicionada.
 * @return true ou false caso a escola ainda não esteja inserida.
 */
bool Empresa::addEscola(Morada *e){
	vector<Morada *>::iterator itb = escolas.begin();
	vector<Morada *>::iterator itf = escolas.end();

	while(itb != itf){
		if(*(*itb) == *e)
			return false;
		itb++;
	}
	mapa->getPontoVertex(e->getID())->setIsSchool(true);
	escolas.push_back(e);
	return true;
}

/**
 * Remove um transporte da frota de veiculos da empresa.
 * @param veiculo Veiculo a ser removido da frota da empresa.
 * @return boleano true ou false consoante seja ou nao possivel remover o veiculo.
 */
bool Empresa::removeTransporte(Veiculo * veiculo)
{
	Veiculo *v;
	for(unsigned int i = 0; i < transportes.size(); i++)
		if(*veiculo == *transportes[i]){
			v = transportes[i];
			transportes.erase(transportes.begin() + i);
			delete(v);
			return true;
		}
	return false;
}

/**
 * Metodo que remove um cliente da empresa.
 * @param cliente Apontador para o cliente a ser removido da empresa.
 * @return True ou false consoante tenha sido removido com sucesso, ou não.
 */
bool Empresa::removeCliente(Cliente * cliente)
{
	Cliente *c;
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(cliente == clientes[i]){
			//falta remover o cliente do ponto de recolha <<<<

			//retira-o do veiculo
			for (size_t var = 0; var < transportes.size(); ++ var) {
				transportes[var]->sairCliente(cliente);
			}
			//retira-o da escola
			removerEscola(cliente->getEscola());
			c = clientes[i];
			clientes.erase(clientes.begin() + i);
			delete(c);
			return true;
		}
	return false;
}

/**
 * Metodo que procura um cliente pelo seu id para depois ser removido
 * @param id Id do cliente.
 * @return boleano que indica o sucesso da operação.
 */
bool Empresa::removeCliente(int id){
	for(unsigned int i = 0; i < clientes.size(); i++)
		if(id == clientes[i]->getID()){
			//encontra o ponto de recolha correspondente e decrementa o numero de criancas
			changeNumCriancas(*clientes[i]->getResidencia(), -1);
			return removeCliente(clientes[i]);
		}
	return false;
}

/**
 * Metodo que remove uma escola da base de dados de escolas da empresa.
 * @param e Escola a remover
 * @param boleano que indica se foi ou não possivel remover a escola em questão.
 */
bool Empresa::removerEscola(Morada *e){
	vector<Cliente *>::iterator itb = clientes.begin();
	vector<Cliente *>::iterator itf = clientes.end();
	vector<Morada *>::iterator itbm = escolas.begin();
	vector<Morada *>::iterator itfm = escolas.end();
	int n = 0;

	//ver se existe outro cliente com a mesma escola
	while(itb != itf){
		if(*(*itb)->getEscola() == *e)
			n++;
		itb++;
	}
	if(n > 1 || n==0)
		return false;
	//ver se a escola pertence as escolas
	while(itbm != itfm){
		if(*(*itbm) == *e){
			delete(*itbm);
			escolas.erase(itbm);
			return true;
		}
		itbm++;
	}
	return false;
}

/**
 *	????
 */
bool compararVeiculos(Veiculo *v1 , Veiculo *v2){
	if(v1->getNumLugares() < v2->getNumLugares())
		return true;
	else
		return false;
}

/**
 * Metodo que faz display do trajeto de ida (empresa->destino) de um veiculo de matriculo 'matricula'.
 * @param matricula Matricula do veiculo que mostrará o seu trajeto.
 * @return True ou false consoante é ou não possivel realizar a operação.
 */

bool Empresa::displayTrajetosIda(string matricula){

	for (size_t i = 0; i < transportes.size(); ++i) {
		if(transportes[i]->getMatricula() == matricula){
			vector<Morada> res = transportes.at(i)->getCaminho();

			for(size_t j = 0; j < res.size(); j++)
				if(!mapa->getPontoProcessado(res.at(j)))
					cout << "o ponto " << res.at(j).getID() << " nao e possivel alcancar devido a impedimentos na via!\n";

			vector<Morada> path = mapa->makePath(res);
			mapa->displayPath(gv, path, 1);
			return true;
		}
	}

	return false;
}

/**
 * Metodo que faz display do trajeto de volta (destino->empresa) de um veiculo de matricula 'matricula'.
 * @param matricula Matricula do veiculo que mostrará o seu trajeto.
 * @return True ou false consoante é ou não possivel realizar a operação.
 */
bool Empresa::displayTrajetosVolta(string matricula){

	for(size_t i = 0; i < transportes.size(); i++){

		if(transportes.at(i)->getMatricula() == matricula){

			vector<Morada> res = transportes.at(i)->getCaminho();

			for(size_t j = 0; j < res.size(); j++)
				if(!mapa->getPontoProcessado(res.at(j)))
					cout << "o ponto " << res.at(j).getID() << " nao e possivel alcancar devido a impedimentos na via!\n";

			vector<Morada> invert;

			for(size_t j = res.size()-1; j > 0; j--)
				invert.push_back(res.at(j));
			invert.push_back(res.at(0));

			vector<Morada> path = mapa->makePath(invert);
			mapa->displayPath(gv,path, 1);
			return true;
		}
	}
	return false;
}

/**
 * Metodo que faz display dos clientes da empresa.
 */
void Empresa::displayClientes() const{
	for (size_t i = 0; i < clientes.size(); ++i) {
		cout << *clientes[i] << endl;
	}
}

/**
 * Metodo que faz display dos veiculos da empresa
 */
void Empresa::displayVeiculos() const{
	for (size_t i = 0; i < transportes.size(); ++i) {
		cout << *transportes[i] << endl;
	}
}

/**
 * Metodo que faz display das escolas (display no mapa)
 */
void Empresa::displayEscolas() const{
	vector<Morada> tmp;

	for (size_t i = 0; i < getEscolas().size(); ++i) {
		tmp.push_back(*getEscolas()[i]);
		cout << tmp[i] << endl;
	}
	mapa->displayPath(gv,tmp, 0);
}

/**
 * Metodo que permite fazer display dos pontos de recolha (display do mapa)
 */
void Empresa::displayPontosRecolha(){
	vector<Morada > pi = mapa->getInterestPoints();

	//fazer algoritmo kmp para saber quantas criancas existem por ponto de recolha
	for (size_t i = 0; i < pi.size(); ++i) {
		vector<Cliente> cli = exactSearch(pi.at(i).getNome());
		cout << pi[i] << " n Clientes: " << cli.size() << endl;
	}

	mapa->displayPath(gv,pi,0);
}

/**
 * M�todo que permite incrementar, decrementar, ou apenas devolver o numero de criancas presentes nesse momemnto numa dada morada.
 */
int Empresa::changeNumCriancas(Morada m, int state){
	Vertex<Morada> *v = mapa->getPontoVertex(m.getID());

	int n = v->getInfo().getNumCriancas();
	n += state;
	m.setNumCriancas(n);

	v->setInfo(m);

	return v->getInfo().getNumCriancas();
}


/**
 * Metodo que distribui os clientes pelos veiculos por proximidade.
 * Este metodo coloca os pontos de interesse sucessivamente, ordenados, no vetor 'caminho' do veiculo correspondente.
 * Um veiculo parte da empresa (primeiro ponto de interesse) e procura o ponto de interesse mais proximo com criancas.
 * Coloca todas as criancas desse ponto na carrinha e procura de novo o ponto de recolha mais proximo com criancas.
 * Quando o veiculo não tem mais lugares a ocupar, verifica quais as escolas que os seus clientes ocupam.
 * Procura a escola mais proxima, depois a seguinte mais proxima  e sempre assim até ter chegado a todas as escolas.
 */
void Empresa::distribuiCliVeiculos(){

	bool end = false;
	vector<Morada > pi; //vetor de apontadores para todos os pontos de interesse
	vector<Morada > temp = mapa->getInterestPoints();

	pi.push_back(*endereco); //comeca na morada da empresa

	mapa->setPontoProcessado(*endereco,true); //o primeiro ponto é processado

	for(size_t i = 0; i < temp.size(); i++)
		pi.push_back(temp.at(i));

	//marca todos os pi com 0 criancas como processados (o primeiro não conta)
	for(size_t i = 1; i < pi.size(); i++){

		vector<Cliente *> clientes = getClientesPontoRecolha(&pi.at(i));
		if(clientes.size() != 0)//vê se o nesse ponto existem criancas
			mapa->setPontoProcessado(pi.at(i), false);
		else
			mapa->setPontoProcessado(pi.at(i), true);
	}

	for(size_t j = 0; j < transportes.size(); j++){

		transportes.at(j)->pushCaminho(*endereco);	//o primeiro ponto a colocar no trajeto é o endereco da empresa

		if(end)
			break;

		int p = 0; // comeca sempre no ponto 0 (indice do vetor pi)
		int min = 0; // ponto mais proximo (indice do vetor pi)
		vector<Morada > dest; //escolas destino

		//marca as escolas como não processadas
		for(size_t i = 0; i < escolas.size(); i++)
			mapa->setPontoProcessado(*escolas.at(i), false);

		while(transportes.at(j)->lugaresLivres() != 0){
			// chamar o grafo para ver se deste ponto de interesse(k), qual o que está mais proximo.
			//Retorna o id do mais proximo.
			min = mapa->getMinDistBetweenPoints(p,pi);

			//se forem iguais chegamos ao fim de todos os pontos de interesse
			if(p == min){
				end = true;
				break;
			}

			transportes.at(j)->pushCaminho(pi.at(min)); 	//colocar  na lifo do veiculo este ponto

			// adiciona as criancas desse destino ao vetor de clientes da carrinha em causa.
			size_t n = 0;
			vector<Cliente *> clientes = getClientesPontoRecolha(&pi.at(min)) ; // clientes por ponto de interesse

			while(transportes.at(j)->lugaresLivres() != 0 && n != clientes.size()){
				transportes.at(j)->addCliente(clientes.at(n));
				changeNumCriancas(pi.at(min),-1);
				mapa->setPontoProcessado(*clientes.at(n)->getEscola(), true); //escola marcada como processada -> é destino
				n++;
			}
			//se todas as criancas entraram no autocarro, esse ponto é marcado como processado
			if(changeNumCriancas(pi.at(min),0) == 0){
				mapa->setPontoProcessado(pi.at(min), true);
			}

			p = min;
		}

		//desobrir quantas escolas diferentes estão no veiculo
		dest.push_back(pi.at(p)); //ultimo ponto
		for(size_t k = 0; k < escolas.size(); k++)
			if(mapa->getPontoProcessado(*escolas.at(k)) == true) //se foram processadas é porque existem alunos no veiculo que as frequentam
				dest.push_back(*escolas.at(k));

		//remarca as escolas como não processadas
		for(size_t i = 0; i < escolas.size(); i++)
			mapa->setPontoProcessado(*escolas.at(i), false);

		//procurar do ultimo ponto a escola mais proxima
		p = 0;
		for(size_t k = 1; k < dest.size(); k++){
			min = mapa->getMinDistBetweenPoints(p,dest);
			if(min != 0)
				mapa->setPontoProcessado(dest.at(min), true);
			transportes.at(j)->pushCaminho(dest.at(min));
			p = min;
		}
	}

	vector<Morada > res = mapa->getInterestPoints();
	//para cada ponto de recolha, colocar o valor original de criancas
	for(size_t j = 0; j < res.size(); j++){
		vector<Cliente *> clientes = getClientesPontoRecolha(&res.at(j));
		for(size_t k = 0; k < clientes.size(); k++)
			changeNumCriancas(res.at(j), 1);
	}

}

/**
 * Inicializacao da empresa. Permite poupar recursos visto que apenas apenas é necessario fazer estes passos 1 vez.
 * Inicia o mapa com todos os pontos. Faz o algoritmo de floyd-Warshall.
 */
void Empresa::initialization(){
	//inicializar o mapa
	gv = new GraphViewer(1200,1200,false);
	gv->createWindow(1200, 1200);
	mapa = new Mapa(gv);
	mapa->makefloydWarshallShortestPath();	//faz o algoritmo
}

void Empresa::update(){
	mapa->makefloydWarshallShortestPath();	//faz o algoritmo
	distribuiCliVeiculos();
}

//==========================================================================================//
// NOVOS M�TODOS CRIADOS PARA O SEGUNDO TRABALHO
//==========================================================================================//

void Empresa::readLast(){
	//l� o ficheiro Last.txt e preenche a empresa com os dados recebidos
	fstream file;
	string line, nome, b;
	stringstream info;
	int id, numCriancas, esc;
	bool isEscola = false;
	vector<int> idEscolas;

	file.open("Last.txt");
	if(file.fail()){
		cout << "Error at opening the file\n";
	}

	// primeiro -> nome da escola
	getline(file,line);
	info << line;
	info >> nome;
	//segundo -> id da escola
	info.clear();
	getline(file,line);
	info << line;
	info >> id;
	//terceiro -> booleano isEscola
	info.clear();
	getline(file,line);
	info << line;
	info >> b;
	if(b == "Y")
		isEscola = true;
	//quarto -> numero de criancas
	info.clear();
	getline(file,line);
	info << line;
	info >> numCriancas;
	while(!file.eof()){
		getline(file,line);
		info.clear();
		info << line;
		info >> esc;
		idEscolas.push_back(esc);
	}

	file.close();

	fillEmpresa(nome, id, isEscola, idEscolas, numCriancas);
}

void Empresa::writeLastAndInfo(){
	//preenche o ficheiro Last.txt
	fstream file;

	file.open("Last.txt");
	if(file.fail()){
		cout << "Error at opening the file\n";
	}

	file << nome << endl << endereco->getID() << endl;
	if(isEscola)
		file << "Y" << endl;
	else
		file << "N" << endl;
	file << clientes.size() << endl;

	for(size_t i = 0; i < escolas.size(); i++){
		file << escolas.at(i)->getID();
		if(i != escolas.size()-1)
			file << endl;
	}
	file.close();

	//reescreve o ficheiro Info.txt
	file.open("Info.txt");
	if(file.fail()){
		cout << "Error at opening the file\n";
	}

	for(size_t j = 0; j < clientes.size(); j++){
		file << clientes.at(j)->getID() << " " << clientes.at(j)->getNome() << ";" << clientes.at(j)->getResidencia()->getID() << " " <<clientes.at(j)->getEscola()->getID();
		if(j != clientes.size()-1)
			cout << endl;
	}
	file.close();
}

void Empresa::fillEmpresa(string nome, int id, bool isEsc, vector<int> escolasID, int numCriancas)
{
	this->isEscola = isEsc;
	this->nome = nome;
	this->endereco = mapa->getPonto(id);

	//cria escolas
	for(size_t i = 0; i < escolasID.size(); i++){
		escolas.push_back(mapa->getPonto(escolasID.at(i)));
		//mapa->getPontoVertex(escolasID.at(i))->setIsSchool(true);
	}

	stringstream info;

	//cria veiculos
	int numVeic = numCriancas/50+1;
	char n = 'a', next;
	string str;
	for(int j = 0; j < numVeic; j++){
		next = n + j;
		info << next;
		info >> str;
		Veiculo *v = new Veiculo(str, 50);
		transportes.push_back(v);
	}

	//cria clientes
	fstream names;

	names.open("Info.txt");
	if(names.fail()){
		cout << "Error at opening the file\n";
	}
	string line, name;
	int idC, id1, id2;
	while(!names.eof()){
		info.clear();
		getline(names,line);
		info << line;
		info >> idC;
		getline(info, line, ';');
		nome = line;
		nome.erase(nome.begin(), nome.begin()+1); // retira o primeiro espaco da palavra
		info >> id1 >> id2;
		Morada *casa = mapa->getPonto(id1);
		Morada *escola = mapa->getPonto(id2);
		Cliente *c = new Cliente(nome,casa);
		if(!hasPR(casa))	//verifica se esta rua j� tem um ponto de recolha, se n�o, passa a ser este ponto
			mapa->setPontoInteresse(*casa,true);
		c->setNovaEscola(escola);
		c->setID(idC);
		addCliente(c);
	}

	names.close();
}

bool Empresa::hasPR(Morada *m){
	vector<Morada > pontos = mapa->getInterestPoints();
	for(size_t i = 0; i < pontos.size(); i++)
		if(pontos.at(i).getNome() == m->getNome())
			return true;
	return false;
}

/**
 * Funcao auxiliar ao algoritmo kmp.
 */
vector<int> Empresa::prefixFunction(string pattern) {

	int m = pattern.length();
	vector<int> pi;

	for(int i = 0; i <= m; i++)
		pi.push_back(0);

	pi.at(0) = -1;

	int j = 0;
	int i = 1;
	while (i <= m) {
		if (pattern[j] == pattern[i]) {
			pi[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0) // j follows a matching prefix
			j = pi[j - 1];
		else { // no match
			pi[i] = 0;
			i++;
		}
	}
	return pi;
}

/**
 * algoritmo kmp que encontra strings iguais num texto
 */
int Empresa::kmp(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();

	int res = 0;

	vector<int> pi = prefixFunction(pattern);

	int i = 0;
	int j = 0;

	while (i < n) {
		if (pattern[j] == text[i]) {
			if (j == m - 1){
				return i - m + 1;	//retorna o local do texto onde encontrou a string
			}else{
				i++;
				j++;
			}
		}
		else if (j > 0)
			j = pi[j + 1];
		else
			i++;
	}
	return -1; //nao encontra
}


/**
 * funcao auxiliar a funcao EditDistance que retorna o minimo de 3 numeros
 */
int Empresa::min(int x, int y, int z){
	int min = x;

	if(y < min)
		min = y;
	if(z < min)
		min = z;

	return min;
}

/**
 * calculo das dist�ncias entre 2 strings
 */
int Empresa::distanceAlgorithm(string street,string streetToSearch) {
	// inicializa��o
	int m = street.length();
	int n = streetToSearch.length();

	int D[m+1][n+1];

	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			D[i][j] = 0;

	for(int i = 0; i < m; i++){
		D[i][0] = i;
	}

	for(int j = 0; j < n; j++){
		D[0][j] = j;
	}

	// recorr�ncia
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			if(street[i-1] == streetToSearch[j-1])
				D[i][j] = D[i-1][j-1];
			else
				D[i][j] = 1 + min(D[i-1][j-1],D[i-1][j],D[i][j-1]);
		}
	}

	// finaliza��o -> retorna a dist�ncia entre as 2 palavras
	return D[m][n];
}

void Empresa::displayClientesMorada(string morada){
	vector<Cliente> cli = exactSearch(morada);

	for(int i = 0; i < cli.size(); i++)
		cout << clientes.at(i)->getID() << " - " << clientes.at(i)->getNome() << endl;
}

void Empresa::proximitySearchMorada(vector<Morada> moradas, string toSearch){
	int n = toSearch.length();
	int m = 0;
	int max = 0;

	for(size_t i = 0; i < moradas.size(); i++){
		int dist = distanceAlgorithm(moradas.at(i).getNome(), toSearch);

		m = moradas.at(i).getNome().length() - 1;
		if(m > n)
			max = m;
		else
			max = n;

		//distancias plausiveis at� metade da maior string
		if(dist < max/2)
			cout << moradas.at(i).getID()<< " - " << moradas.at(i).getNome() << endl;
	}
}

void Empresa::proximitySearchClient(string nome){

	int n = nome.length();
	int m = 0;
	int max = 0;

	for(size_t i = 0; i < clientes.size(); i++){
		int dist = distanceAlgorithm(clientes.at(i)->getNome(), nome);

		m = clientes.at(i)->getNome().length() - 1;
		if(m > n)
			max = m;
		else
			max = n;

		//distancias plausiveis at� metade da maior string
		if(dist < max/2)
			cout << clientes.at(i)->getID()<< " - " << clientes.at(i)->getNome() << endl;
	}
}

vector<Cliente> Empresa::exactSearch(string morada){
	vector<Cliente> res;
	for(size_t i = 0; i < clientes.size(); i++)
		if(kmp(clientes[i]->getResidencia()->getNome(),morada) != -1)//moradas exatamante iguais
			res.push_back(*clientes.at(i));
	return res;
}

//true->encontrou igual
void Empresa::exactSearch4Test(string nome){
	for(size_t i = 0; i < clientes.size(); i++)
		if(kmp(clientes[i]->getNome(),nome) != -1)
			cout << clientes.at(i)->getID() << " - " << clientes.at(i)->getNome() << endl;
}
