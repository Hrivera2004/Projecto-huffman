#include <iostream>
#include "Nodo.h"
#include "Huffman_Tree.h"
using namespace std;

void mostrarMenu() {
	cout << "\n--- Menu ---\n";
	cout << "1. Mostrar cola de prioridades\n";
	cout << "2. Mostrar tabla de frecuencias\n";
	cout << "3. Salir\n";
	cout << "Seleccione una opción: ";
}

int main() {
	Huffman_Tree huffmanTree;
	int opcion = 0;
	string filename = "ppp.txt";  // Nombre del archivo de texto a leer
	huffmanTree.lectura_txt(filename);  // Generar tabla de frecuencias

	do {
		mostrarMenu();
		cin >> opcion;
		switch (opcion) {
		case 1:
			cout << "\n--- Cola de Prioridades (Ordenada) ---\n";
			huffmanTree.ordenarCola();
			huffmanTree.print();  // Mostrar cola de prioridades ordenada
			break;
		case 2:
			cout << "\n--- Tabla de Frecuencias ---\n";
			huffmanTree.print();  // Mostrar tabla de frecuencias
			break;
		case 3:
			cout << "\n--- Saliendo del Programa... ---\n";
			break;
		default:
			cout << "Opción no válida. Intente nuevamente.\n";
		}
	} while (opcion != 3);
	return 0;
}