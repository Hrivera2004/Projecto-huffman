#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include "Nodo.h"
#include "Huffman_Tree.h"
using namespace std;

void mostrarMenu() {
    system("cls");
    cout << "\n--- Menu ---\n";
    cout << "1. Mostrar cola de prioridades\n";
    cout << "2. Mostrar tabla de frecuencias\n";
    cout << "3. Mostrar arbol\n";
    cout << "4. Comprimir\n";
    cout << "5. Descomprimir\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    setlocale(LC_ALL, "spanish");

    Huffman_Tree huffmanTree("");  // Declarar el árbol sin archivo

    string nameFiletxt;
    bool archivoValido = false;

    // Solicitar el nombre del archivo hasta que sea válido
    while (!archivoValido) {
        cout << "Ingrese el nombre del archivo de texto: ";
        cin >> nameFiletxt;

        // Asignar el nombre de archivo al árbol
        huffmanTree.setArchivo("Files/"+nameFiletxt);

        // Verificar si la lectura del archivo es correcta
        if (huffmanTree.lectura_txt() != 0) {
            cout << endl;
            cout << "Error al leer el archivo: " << nameFiletxt << ". Intente nuevamente.\n";
            cout << endl;
        }
        else {
            archivoValido = true;  // Archivo leído correctamente
            huffmanTree.build_tree();  // Construir el árbol solo cuando el archivo es válido
        }
    }

    int opcion = 0;

    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "\n--- Cola de Prioridades (Ordenada) ---\n";
            huffmanTree.ordenarCola();
            huffmanTree.print_cola();  // Mostrar cola de prioridades ordenada
            system("pause");
            break;
        case 2:
            cout << "\n--- Tabla de Frecuencias ---\n";
            huffmanTree.print_TF();  // Mostrar tabla de frecuencias
            system("pause");
            break;
        case 3:
            cout << "\n--- Arbol Huffman (imprimir) ---\n";
            huffmanTree.print_tree();
            system("pause");
            break;
        case 4:
            huffmanTree.comprimir();  // Comprimir el archivo
            cout << "\n--- Compresión completada ---\n";
            system("pause");
            break;
        case 5: {
            cout << "\n--- Descomprir Archivo ---\n";
            cout << "Ingrese el nombre del archivo: ";
            string archivo_descomprimir = "";
            cin >> archivo_descomprimir;
            huffmanTree.descomprimir("Files/" + archivo_descomprimir);
            system("pause");
        }break;
        case 6:
            cout << "\n--- Saliendo del Programa... ---\n";
            break;
        default:
            cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 6);

    return 0;
}