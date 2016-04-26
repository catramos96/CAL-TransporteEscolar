#ifndef SRC_EXCECOES_H_
#define SRC_EXCECOES_H_

#include "Morada.h"

/**
 * @brief Classe que representa uma excecao da classe Main.
 * Esta excecao e lancada quando a opcao colocada nao esta entre os limites estabelecidos.
 * E uma classe template pois pode receber mais que um tipo de dados.
 */
template<class N>
class OpccaoInvalida {
private:
	N op; /**< membro privado que representa a opcao colocada */
	N min; /**< membro privado que representa a opcao minima */
	N max; /**< membro privado que representa a opcao maxima */
public:
	/**
	 * @brief Construtor.
	 * Inicializa os membros op, min e max com, repetivamente, a opcao escolhida, a opcao minima e a opcao maxima.
	 * @param op Opcao escolhida.
	 * @param min Opcao minima.
	 * @param max Opcao maxima.
	 */
	OpccaoInvalida(N op, N min, N max) {
		this->op = op;
		this->min = min;
		this->max = max;
	}
	;
	/*
	 * @brief Funcao que retorna a opcao minima.
	 * @return Opcao minima.
	 */
	N getMin() const {
		return min;
	}
	;
	/*
	 * @brief Funcao que retorna a opcao maxima.
	 * @return Opcao maxima.
	 */
	N getMax() const {
		return max;
	}
	;
	/**
	 * @brief Funcao que retorna a opcao escolhida.
	 * @return Opcao escolhida.
	 */
	N getOp() const {
		return op;
	}
	;
};

/**
 * @brief Classe que representa uma excecao da classe main.
 * Permite ter a opcao de voltar a tras nos menus.
 */
class VoltarAtras {
};

/**
 * @brief Classe que representa uma excecao da classe main.
 * Impede que o programa aborte quando sao introduzidos valores errados no buffer.
 */
class InputFail {
};

/**
 * @brief Classe que representa uma excecao que e lancada quando um Cliente ja existe.
 */
class ClienteJaExiste {
private:
	string nome;/**< membro privado que representa o nome do cliente*/
	Morada escola;/**< membro privado que representa a escola do cliente */
	Morada residencia;/**< membro privado que representa a residencia do cliente */
public:
	/*
	 *  @brief Construtor da classe ClienteJaExiste
	 *  @param n (string), nome do cliente
	 *  @param e (Morada), escola do cliente
	 *  @param r (Morada), residencia do cliente
	 */
	ClienteJaExiste(string n, Morada e, Morada r){
		nome = n;
		escola = e;
		residencia = r;
	};
	/*
	 * @brief Funcao que retorna o nome do ClienteJaExiste
	 * @return nome (string)
	 */
	string getNome(){return nome;};
	/*
	 * @brief Funcao que retorna a escola do ClienteJaExiste
	 * @returne escola (Morada)
	 */
	Morada getMoradaEscola(){return escola;};
	/*
	 * @brief Funcao que retorna a residencia do ClienteJaExiste
	 * @return residencia (Morada)
	 */
	Morada getMoradaResidencia(){return residencia;};
};

/*
 * @brief Classe que e usada para lancar uma excecao quando estamos a lidar com um cliente que nao existe.
 */
class ClienteInexistente {
private:
	int id;/**< membro privado que representa o id do cliente*/
public:
	/*
	 * @brief Construtor da classe ClienteInexistente
	 * @param id (int)
	 */
	ClienteInexistente(int id){
		this->id = id;
	};
	/*
	 * @brief Funcao que retorna o id do ClienteInexistente
	 * @return id (int)
	 */
	int getID(){return id;};
};

/*
 * @brief Classe que e usada para lancar a excecao PontoInexistente quando estamos a lidar com uma Morada que nao existe.
 */
class PontoInexistente {
private:
	Morada ponto;/**< membro privado que representa a Morada do PontoInexistente*/
public:
	/*
	 * @brief Construtor da classe PontoInexistente
	 * @param p (Morada)
	 */
	PontoInexistente(Morada p){ponto = p;};
	/*
	 * @brief Funcao que retorna o ponto que e inexistente
	 * @return ponto (Morada)
	 */
	Morada getPonto(){
		return ponto;
	};
};

/*
 * @brief Classe que e usada para lancar a excecao VeiculoJaExiste quando estamos a lidar com um veiculo que ja existe.
 */
class VeiculoJaExiste {
private:
	string matricula;/**< membro privado que representa a matricula do Veiculo*/
public:
	/*
	 * @brief Contrutor da classe VeiculoJaExiste
	 * @param m (string), matricula
	 */
	VeiculoJaExiste(string m){
		matricula = m;
	};
	/*
	 * @brief Funcao que retorna a matricula do VeiculoJaExiste
	 * @matricula (string)
	 */
	string getMatric() const{
		return matricula;
	}
};

/*
 * @brief Classe que e usada para lancar uma excecao quando lidamos com um veiculo que nao existe.
 */
class VeiculoInexistente {
private:
	string matricula;/**< membro privado que representa a matricula do Veiculo*/
public:
	/*
	 * @brief Construtor da classe VeiculoInexistente
	 * @param m (string), matricula
	 */
	VeiculoInexistente(string m){
		matricula = m;
	};
	/*
	 * @brief Funcao que retorna a matricula do VeiculoInexistente
	 * @return matricula (string)
	 */
	string getMatric() const{
		return matricula;
	}
};

/*
 * @brief Classe que e usada para lancar uma excecao quando lidamos com uma Morada residencia que nao e valida.
 * Uma residencia nao e valida quando tambem e uma escola ou um ponto que nao e um ponto de recolha.
 * Os pontos de recolha sao os pontos onde tem uma paragem de autocarro.
 */
class ResidenciaInvalida {
private:
	Morada r;/**< membro privado que representa a Morada residencia do Cliente*/
public:
	/*
	 * @brief Construtor da Classe ResidenciaInvalida
	 * @param m (Morada), residencia
	 */
	ResidenciaInvalida(Morada m){r = m;};
	/*
	 * @brief Funcao que retorna a morada da ResidenciaInvalida
	 * @return r (Morada), residencia
	 */
	Morada getResidencia() const {return r;};
};

/*
 * @brief Classe que e usada para lancar a excecao VeiculosInsuficientes.
 * Esta classe e usada quando temos um numero de lugares total menor que o numero de clientes.
 */
class VeiculosInsuficientes{
};

/*
 * @brief Classe que e usada para lancar uma excecao quando um ponto de recolha nao e valido.
 * Um ponto de recolha nao e valido quando tem a morada da propria empresa, de uma escola ou quando
 * nao e possivel chegar a esse ponto e/ou voltar desse ponto.
 */
class PontoRecolhaInvalido{
	Morada p;/**< membro privado que representa a morada do PontoRecolhaInvalido*/
public:
	/*
	 * @brief Construtor da Classe PontoRecolhaInvalido
	 * @param p (Morada), ponto de recolha
	 */
	PontoRecolhaInvalido(Morada p){this->p = p;};
	/*
	 * @brief Funcao que retorna a morada do PontoRecolhaInvalido.
	 * @return p (Morada), ponto de recolha invalido.
	 */
	Morada getPonto() const {return p;};
};

#endif /* SRC_EXCECOES_H_ */
