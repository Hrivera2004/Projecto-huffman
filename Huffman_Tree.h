#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include<bitset>
#include "Nodo.h"
using namespace	std;

class Huffman_Tree {
private:
	Nodo* head;
	vector<Nodo*> cola;
	vector<Nodo*> copia_cola;
	string txt_filename;
	unordered_map<char, string> codigo;
public:

	Huffman_Tree(string txt_filename) {
		head = nullptr;
		this->txt_filename = txt_filename;
	}

	~Huffman_Tree() {
		deleteTree(head);
		cola.clear();
		copia_cola.clear();
	}

	void deleteTree(Nodo* nodo) {
		if (nodo != nullptr) {
			deleteTree(nodo->getLeft_P());
			deleteTree(nodo->getRight_P());
			delete nodo;
		}
	}
	void setArchivo(const string& nuevoArchivo) {
		this->txt_filename = nuevoArchivo;
	}
	int lectura_txt() {//probado
		ifstream lectura;
		lectura.open(txt_filename + ".txt");
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

	void build_tree() {//probado
		ordenarCola();
		copia_cola = cola;
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
		for (size_t i = 0; i < copia_cola.size(); i++) {
			cout << "'" << copia_cola[i]->getChar() << "' aparece " << copia_cola[i]->getFreq() << " veces." << endl;
		}
	}
	void print_TF() { // falta  [% de compression lograda , codigo binario]
		pre_order(head, "");
	}

	void pre_order(Nodo* nodo, string progress) {
		if (nodo->getChar() != '\0') {
			// Alinear la salida con setw
			cout << setw(5) << "'" << nodo->getChar() << "'"
				<< setw(12) << "aparece " << setw(3) << nodo->getFreq() << " veces."
				<< setw(10) << "binario: " << setw(10) << progress
				<< " Compression logrado: "
				<< setw(7) << fixed << setprecision(2) << (1.0 - (progress.size() / 8.0)) * 100 << "%"
				<< endl;
			codigo[nodo->getChar()] = progress;
		}
		else {
			if (nodo->getLeft_P() != nullptr) {
				pre_order(nodo->getLeft_P(), progress + '0');
			}
			if (nodo->getRight_P() != nullptr) {
				pre_order(nodo->getRight_P(), progress + '1');
			}
		}
	}
	void pre_order_comprimir(Nodo* nodo, string progress) {
		if (nodo->getChar() != '\0') {
			codigo[nodo->getChar()] = progress;
		}
		else {
			if (nodo->getLeft_P() != nullptr) {
				pre_order(nodo->getLeft_P(), progress + '0');
			}
			if (nodo->getRight_P() != nullptr) {
				pre_order(nodo->getRight_P(), progress + '1');
			}
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
		for (size_t i = 0; i < nivel; ++i) {
			cout << "   ";  // Indentación para reflejar el nivel del árbol
		}

		// Si es un nodo hoja, imprime el carácter y la frecuencia
		if (nodo->getChar() != '\0') {
			cout << "'" << nodo->getChar() << "' (Frecuencia: " << nodo->getFreq() << ")" << endl;
		}
		// Si es un nodo interno, solo imprime la frecuencia
		else {
			cout << "[Nodo] (" << nodo->getFreq() << ")" << endl;
		}

		// Llamadas recursivas para los hijos izquierdo y derecho
		imprimir_arbol(nodo->getLeft_P(), nivel + 1);  // Imprimir el subárbol izquierdo
		imprimir_arbol(nodo->getRight_P(), nivel + 1); // Imprimir el subárbol derecho
	}

	void print_tree() {
		imprimir_arbol(head);
	}

	void comprimir() {
		if (codigo.size() == 0) {
			pre_order_comprimir(head, "");
		}

		// Leer el archivo de entrada y reemplazar los caracteres por los códigos Huffman
		ifstream input(txt_filename + ".txt");
		ofstream output(txt_filename + ".comp", ios::binary);
		if (!input.is_open() || !output.is_open()) {
			cout << "Error al abrir los archivos de entrada/salida" << endl;
			return;
		}

		//guradar "arbol"
		ofstream write(txt_filename + ".huffman", ios::binary);
		guardar_arbol_binario(head, write);
		write.close();

		string compressed_data = "";
		char c;
		while (input.get(c)) {
			compressed_data += codigo[c];  // Reemplazar el carácter por su código Huffman
		}

		int paddding = 0;
		// Escribir la secuencia comprimida (convertir de string a bits)
		vector<unsigned char> bytes;
		for (size_t i = 0; i < compressed_data.size(); i += 8) {
			string byte_str = compressed_data.substr(i, 8);
			if (byte_str.size() < 8) {
				paddding = 8 - byte_str.size();
				byte_str.append(8 - byte_str.size(), '0');
			}
			bytes.push_back(bitset<8>(byte_str).to_ulong());
		}
		output.write(reinterpret_cast<char*>(&paddding), sizeof(int));

		for (size_t i = 0; i < bytes.size(); i++){
			unsigned char byte = bytes[i];
			output.write(reinterpret_cast<char*>(&byte), sizeof(byte));
		}
		
		input.close();
		output.close();
	
	}
	void guardar_arbol_binario(Nodo* nodo, ofstream& file) {
		if (!nodo) return;

		// Si es una hoja, escribimos el bit 1 seguido del carácter en binario
		if (nodo->getLeft_P() == nullptr && nodo->getRight_P() == nullptr) {
			file.put('1');  // Nodo hoja
			file.put(nodo->getChar());  // Guardamos el carácter en binario
		}
		else {
			file.put('0');  // Nodo interno
		}

		// Guardamos recursivamente los hijos
		guardar_arbol_binario(nodo->getLeft_P(), file);
		guardar_arbol_binario(nodo->getRight_P(), file);
	}

	void descomprimir(string comp_name) {
		//lectura del arbol
		ifstream input(comp_name + ".huffman", ios::binary);
		Nodo* temp_head = cargar_arbol_binario(input);
		input.close();
		//lectura de boolean
		ifstream input2(comp_name + ".comp", ios::binary);
		int padding;
		input2.read(reinterpret_cast<char*>(&padding), sizeof(int));
		//lectura de frase comprimida
		
		string compressed_data = "";
		unsigned char byte;
		while (input2.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
			compressed_data += bitset<8>(byte).to_string();  // Convertir los bytes de vuelta a bits
		}
		compressed_data.erase(compressed_data.size() - padding);

		//traducir frase
		string frase = "";
		Nodo* actual = temp_head; //escribir en txt
		for (size_t i = 0; i < compressed_data.size(); i++) {
			if (compressed_data[i] == '0'){
				actual = actual->getLeft_P();
			} else {
				actual = actual->getRight_P();
			}
			if (actual->getLeft_P() == nullptr && actual->getRight_P() == nullptr) {
				frase += actual->getChar();
				actual = temp_head;
			}
		}
		
		cout << frase << endl;
		input2.close();
	}

	Nodo* cargar_arbol_binario(ifstream& file) {
		char bit;
		file.get(bit);

		// Si es una hoja (bit 1), leemos el carácter
		if (bit == '1') {
			char caracter;
			file.get(caracter);
			return new Nodo(caracter, 0);  // El nodo hoja no tiene frecuencia relevante aquí
		}

		// Si es un nodo interno (bit 0), creamos un nodo y seguimos cargando recursivamente
		if (bit == '0') {
			Nodo* nodo = new Nodo('\0', 0);  // Nodo interno sin carácter
			nodo->setLeft_P(cargar_arbol_binario(file));  // Cargar subárbol izquierdo
			nodo->setRight_P(cargar_arbol_binario(file));  // Cargar subárbol derecho
			return nodo;
		}

		return nullptr;  // En caso de error
	}

	
};