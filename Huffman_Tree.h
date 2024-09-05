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

	int lectura_txt(string filename) {
		ifstream lectura;
		lectura.open(filename);
		if (!lectura) {
			cout << "-- lectura fallida --";
			return 1;
		}
		char caracter = ' ';
		while (lectura.get(caracter)) {
			if (!find){
				Nodo* nodo = new Nodo(caracter);
				cola.push_back(nodo);
			}
		}
		return 0;
	}

	bool find(char chr) {
		for (size_t i = 0; i < cola.size(); i++){
			if (cola[i]->getChar() == chr) {
				cola[i]->increase_Freq();
				return true;
			}
		}
		return false;
	}

};