#include <iostream>
#include "Nodo.h"
#include "Huffman_Tree.h"
using namespace std;

void mostrarMenu() {
	cout << "\n--- Menu ---\n";
	cout << "1. Mostrar cola de prioridades\n";
	cout << "2. Mostrar tabla de frecuencias\n";
	cout << "3. Mostrar arbol\n";
	cout << "4. Comprimir\n";
	cout << "5. Salir\n";
	cout << "Seleccione una opción: ";
}

int main() {
	setlocale(LC_ALL, "spanish");
	Huffman_Tree huffmanTree("ppp");
	int opcion = 0;
	huffmanTree.lectura_txt();  // Generar tabla de frecuencias
	huffmanTree.build_tree();
	do {
		mostrarMenu();
		cin >> opcion;
		switch (opcion) {
		case 1:
			cout << "\n--- Cola de Prioridades (Ordenada) ---\n";
			huffmanTree.ordenarCola();
			huffmanTree.print_cola();  // Mostrar cola de prioridades ordenada
			break;
		case 2:
			cout << "\n--- Tabla de Frecuencias ---\n";
			huffmanTree.print_TF();  // Mostrar tabla de frecuencias
			break;
		case 3:
			cout << "\n--- Arbol huffman (imprimir) ---\n";
			huffmanTree.print_tree();
			break;
		case 4:
			huffmanTree.comprimir();
			break;
		case 5:
			cout << "\n--- Saliendo del Programa... ---\n";
			break;
		default:
			cout << "Opción no válida. Intente nuevamente.\n";
		}
	} while (opcion != 5);
	return 0;
}