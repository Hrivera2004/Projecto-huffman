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
	Nodo* head = NULL;
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
			if (!find(caracter)) {
				Nodo* nodo = new Nodo(caracter);
				cola.push_back(nodo);
			}
		}
		head = cola[0];
		lectura.close();  // Cerrar archivo después de leer
		return 0;
	}

	void build_tree() {//falta probar
		while (cola.size() > 1) {
			cola.push_back(inner_node_create());
			ordenarCola();
		}
	}

	Nodo* inner_node_create() {//falta probar
		Nodo* nodo1 = cola[cola.size() - 1];
		Nodo* nodo2 = cola[cola.size() - 2];
		cola.pop_back();
		cola.pop_back();
		return new Nodo('\0', nodo1->getFreq() + nodo2->getFreq(), nodo2, nodo1);
	}

	void print() {
		cout << "Tabla de frecuencias de caracteres:\n";
		for (size_t i = 0; i < cola.size(); i++) {
			cout << "'" << cola[i]->getChar() << "' aparece " << cola[i]->getFreq() << " veces." << endl;
		}
	}

	bool find(char chr) {//probado
		for (size_t i = 0; i < cola.size(); i++) {
			if (cola[i]->getChar() == chr) {
				cola[i]->increase_Freq();
				return true;
			}
		}
		return false;
	}

	// Método para ordenar la cola usando MergeSort (de mayor a menor frecuencia)
	void ordenarCola() {
		if (cola.size() > 1) {
			realizarMergeSort(cola, 0, cola.size() - 1);
		}
	}

	// Función de MergeSort
	void realizarMergeSort(vector<Nodo*>& listaNodos, int indiceInicio, int indiceFin) {
		if (indiceInicio < indiceFin) {
			int indiceMitad = (indiceInicio + indiceFin) / 2;
			realizarMergeSort(listaNodos, indiceInicio, indiceMitad); // Ordenar first mitad
			realizarMergeSort(listaNodos, indiceMitad + 1, indiceFin); // Ordenar second mitad
			mezclarSublistas(listaNodos, indiceInicio, indiceMitad, indiceFin); // Mezclar both mitades
		}
	}

	// Función para mezclar las dos mitades del vector de nodos
	void mezclarSublistas(vector<Nodo*>& listaNodos, int indiceInicio, int indiceMitad, int indiceFin) {
		int tamanoIzquierda = indiceMitad - indiceInicio + 1; // Tamaño de la sublista izquierda
		int tamanoDerecha = indiceFin - indiceMitad; // Tamaño de la sublista derecha

		// Subvectores temporales
		vector<Nodo*> subListaIzquierda(tamanoIzquierda);
		vector<Nodo*> subListaDerecha(tamanoDerecha);

		// Copiar data subvectores temporales
		for (int indiceIzquierda = 0; indiceIzquierda < tamanoIzquierda; indiceIzquierda++)
			subListaIzquierda[indiceIzquierda] = listaNodos[indiceInicio + indiceIzquierda];
		for (int indiceDerecha = 0; indiceDerecha < tamanoDerecha; indiceDerecha++)
			subListaDerecha[indiceDerecha] = listaNodos[indiceMitad + 1 + indiceDerecha];

		int indiceIzquierda = 0;
		int indiceDerecha = 0;
		int indiceMezcla = indiceInicio;

		// Mezclar
		while (indiceIzquierda < tamanoIzquierda && indiceDerecha < tamanoDerecha) {
			if (subListaIzquierda[indiceIzquierda]->getFreq() >= subListaDerecha[indiceDerecha]->getFreq()) {
				listaNodos[indiceMezcla] = subListaIzquierda[indiceIzquierda];
				indiceIzquierda++;
			}
			else {
				listaNodos[indiceMezcla] = subListaDerecha[indiceDerecha];
				indiceDerecha++;
			}
			indiceMezcla++;
		}

		// Copiar subIzq
		while (indiceIzquierda < tamanoIzquierda) {
			listaNodos[indiceMezcla] = subListaIzquierda[indiceIzquierda];
			indiceIzquierda++;
			indiceMezcla++;
		}

		// Copiar subder
		while (indiceDerecha < tamanoDerecha) {
			listaNodos[indiceMezcla] = subListaDerecha[indiceDerecha];
			indiceDerecha++;
			indiceMezcla++;
		}
	}
};