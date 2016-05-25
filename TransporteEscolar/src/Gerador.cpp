#include "Gerador.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

Gerador::Gerador(int numNames, bool isEscola){

	e = new Empresa();

	srand (time(NULL));

	fstream file;
	fstream names;

	file.open("Info.txt");
	if(file.fail()){
		cout << "Error at opening the file\n";
	}

	names.open("Names.txt");
	if(names.fail()){
		cout << "Error at opening the file\n";
	}

	string nome;
	int idEmpresa;

	//empresa
	if(isEscola)
		nome = "Escola";
	else
		nome = "Empresa";

	int rangeMax = e->getMapa()->getIDMax();
	int id = rand() % rangeMax+1;

	idEmpresa = id;

	//ids das escolas -> nao faz mal haver numeros repetidos, simplemente a escola tem mais capacidade
	vector<int> escolas;

	if(!isEscola){
		int numEsc = numNames/200+1;
		int i = 0;
		while(i < numEsc){
			id = rand() % rangeMax+1;
			if(id != idEmpresa){
				escolas.push_back(id);
				i++;
			}
		}
		//retira repetidas
	}else
		escolas.push_back(idEmpresa);

	//clientes
	string line;
	int casa, esc;
	for (size_t i = 1; i <= numNames; i++) {
		getline(names, line);

		//id da casa nao sobreposto ao das escolas ou da empresa
		bool repetido = false;
		while(true){
			casa = rand() % rangeMax+1;
			for(size_t j = 0; j < escolas.size(); j++)
				if(escolas.at(j) == casa)
					repetido = true;
			if(!repetido && casa != idEmpresa)
				break;
		}

		file << i << " " << line << ";" << casa << " " <<escolas.at(rand() % escolas.size());

		if(i != numNames)
			file << endl;
	}

	file.close();
	names.close();

	e->fillEmpresa(nome,idEmpresa,isEscola,escolas,numNames);
}

Empresa *Gerador::getEmpresa(){
	return e;
}
