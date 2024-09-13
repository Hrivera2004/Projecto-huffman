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
	vector<Nodo*> copia_cola;
public:
	
	Huffman_Tree() {
		head = nullptr;
	}
	
	~Huffman_Tree() {
		//destructor al final
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
		copia_cola = cola;
		lectura.close();  // Cerrar archivo después de leer
		return 0;
	}

	void build_tree() {//probado
		ordenarCola();
		while (cola.size() > 1) {
			cola.push_back(inner_node_create());
			ordenarCola();
		}
		head = cola.back();
	}

	Nodo* inner_node_create() {//probado
		Nodo* nodo1 = cola.back();
		cola.pop_back();
		Nodo* nodo2 = cola.back();
		cola.pop_back();
		return new Nodo('\0', nodo1->getFreq() + nodo2->getFreq(), nodo2, nodo1);
	}

	void print_cola() {
		for (size_t i = 0; i < cola.size(); i++) {
			cout << "'" << copia_cola[i]->getChar() << "' aparece " << copia_cola[i]->getFreq() << " veces." << endl;
		}
	}
	void print_TF() { // falta  [% de compression lograda , codigo binario]
		for (size_t i = 0; i < cola.size(); i++) {
			cout << "'" << copia_cola[i]->getChar() << "' aparece " << copia_cola[i]->getFreq() << " veces." << endl;
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
	void imprimir_arbol(Nodo* nodo, int nivel = 0) {
		if (nodo == nullptr) {
			return;  // Si el nodo es nulo, no se imprime nada
		}

		// Imprimir la información del nodo con la indentación adecuada
		for (int i = 0; i < nivel; ++i) {
			cout << "   ";  // Indentación para reflejar el nivel del árbol
		}

		// Si es un nodo hoja, imprime el carácter y la frecuencia
		if (nodo->getChar() != '\0') {
			cout << "'" << nodo->getChar() << "' (Frecuencia: " << nodo->getFreq() << ")" << endl;
		}
		// Si es un nodo interno, solo imprime la frecuencia
		else {
			cout << "[Nodo interno] (Frecuencia: " << nodo->getFreq() << ")" << endl;
		}

		// Llamadas recursivas para los hijos izquierdo y derecho
		imprimir_arbol(nodo->getLeft_P(), nivel + 1);  // Imprimir el subárbol izquierdo
		imprimir_arbol(nodo->getRight_P(), nivel + 1); // Imprimir el subárbol derecho
	}

	void print_tree() {
		imprimir_arbol(head);
	}


};