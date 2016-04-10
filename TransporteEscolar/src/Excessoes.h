#ifndef SRC_EXCESSOES_H_
#define SRC_EXCESSOES_H_

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



#endif /* SRC_EXCESSOES_H_ */
