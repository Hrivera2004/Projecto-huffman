#pragma once
class Nodo {
	private:
		char caracter;
		int frequencia;
		Nodo* array_children[2];
		Nodo* parent;
	public:
		//constructores
		~Nodo() {

		} //implementar solo si necesario
		Nodo(char caracter, int frequencia, Nodo* children_L, Nodo* children_R) {
			this->caracter = caracter;
			this->frequencia = frequencia;
			array_children[0] = children_L;
			array_children[1] = children_R;
			parent = nullptr;
		}
		Nodo(char caracter, int frequencia) {
			this->caracter = caracter;
			this->frequencia = frequencia;
			array_children[0] = nullptr;
			array_children[1] = nullptr;
			parent = nullptr;
		}
		Nodo(char caracter) {
			this->caracter = caracter;
			frequencia = 0;
			array_children[0] = nullptr;
			array_children[1] = nullptr;
			parent = nullptr;
		}
		//setters and getters

		char getChar() {
			return caracter;
		}
		void setChar(char caracter) {
			this->caracter = caracter;
		}

		int getFreq() {
			return frequencia;
		}
		void setFreq(int Freq) {
			frequencia = Freq;
		}

		void setLeft_P(Nodo* nodo) {
			array_children[0] = nodo;
		}
		Nodo* getLeft_P() {
			return array_children[0];
		}

		void setRight_P(Nodo* nodo) {
			array_children[1] = nodo;
		}
		Nodo* getRight_P() {
			return array_children[1];
		}
		//methodos
		void increase_Freq() {
			frequencia++;
		}
	};

