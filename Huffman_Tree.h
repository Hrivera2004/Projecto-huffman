#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include "Nodo.h"

using namespace	std;

class Huffman_Tree {
private:
	Nodo* head;
	vector<Nodo*> cola; // implementar como cola sino toca usar un quicksort (talvez no)
public:
	Huffman_Tree() {

	}
	int lectura_txt(string filename) {//probado
		ifstream lectura;
		lectura.open(filename);
		if (!lectura) {
			cout << "-- lectura fallida --";
			return 1;
		}
		char caracter = ' ';
		while (lectura.get(caracter)) {
			if (!find(caracter)){
				Nodo* nodo = new Nodo(caracter);
				cola.push_back(nodo);
			}
		}
		head = cola[0]; 
		print();
		return 0;
	}
	
	void build_tree() {//falta probar
		while (cola.size() > 1){
			cola.push_back(inner_node_create());
			//llamar ordenamiento
		}
	}

	Nodo* inner_node_create() {//falta probar
		Nodo* nodo1 = cola[cola.size() - 1];
		Nodo* nodo2 = cola[cola.size() - 2];
		cola.pop_back();
		cola.pop_back();
		return new Nodo('\0',nodo1->getFreq() + nodo2->getFreq(), nodo2, nodo1);
	}
	void print() {//probado
		for (size_t i = 0; i < cola.size(); i++){
			cout << cola[i]->getChar()<< " " << cola[i]->getFreq()<< endl;
		}
	}
	bool find(char chr) {//probado
		for (size_t i = 0; i < cola.size(); i++){
			if (cola[i]->getChar() == chr) {
				cola[i]->increase_Freq();
				return true;
			}
		}
		return false;
	}

};