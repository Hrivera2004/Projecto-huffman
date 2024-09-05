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
	vector<Nodo*> cola; // implementar como cola sino toca usar un quicksort
public:
	int lectura_txt(string filename) {
		ifstream lectura;
		lectura.open(filename);
		if (!lectura) {
			cout << "-- lectura fallida";
			return 1;
		}
		char caracter = ' ';
		while (lectura.get(caracter)) {

			//crear nodo y añadir a cola de manera ya orenada
		}
	}

};