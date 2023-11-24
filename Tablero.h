#pragma once
#include <iostream>
#include <vector>

using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;

class Tablero {
private:
    vector<vector<char>> tablero;

public:
   Tablero() : tablero(FILAS, vector<char>(COLUMNAS, ' ')) {}

    bool columnaLlena(int columna) const {
        return tablero[0][columna] != ' ';
    }

    bool tableroLleno() const {
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            if (!columnaLlena(columna)) {
                return false;
            }
        }
        return true;
    }

    void deshacerMovimiento(int columna) {
        for (int i = 0; i < FILAS; ++i) {
            if (tablero[i][columna] != ' ') {
                tablero[i][columna] = ' ';
                break;
            }
        }
    }

    void imprimir() const {
        for (int i = 0; i < FILAS; ++i) {
            cout << "|";
            for (int j = 0; j < COLUMNAS; ++j) {
                cout << tablero[i][j] << "|";
            }
            cout << '\n';
        }
        cout << '\n';
    }

    bool validarColumna(int columna) const {
        return columna >= 0 && columna < COLUMNAS;
    }

    bool colocarFicha(int columna, char jugador) {
        for (int i = FILAS - 1; i >= 0; --i) {
            if (tablero[i][columna] == ' ') {
                tablero[i][columna] = jugador;
                return true;
            }
        }
        return false;
    }

    bool verificarGanadorEnLinea(const vector<char>& linea, char jugador) const {
        for (int i = 0; i <= COLUMNAS - 4; ++i) {
            if (linea[i] == jugador && linea[i + 1] == jugador && linea[i + 2] == jugador && linea[i + 3] == jugador) {
                return true;
            }
        }
        return false;
    }

    bool verificarGanador(char jugador) const {
        // Verificar en horizontal
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == jugador &&
                tablero[i][j + 1] == jugador &&
                tablero[i][j + 2] == jugador &&
                tablero[i][j + 3] == jugador) {
                return true;
            }
        }
    }

    // Verificar en vertical
    for (int j = 0; j < COLUMNAS; ++j) {
        for (int i = 0; i <= FILAS - 4; ++i) {
            if (tablero[i][j] == jugador &&
                tablero[i + 1][j] == jugador &&
                tablero[i + 2][j] == jugador &&
                tablero[i + 3][j] == jugador) {
                return true;
            }
        }
    }

    // Verificar en diagonal (de izquierda a derecha)
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == jugador &&
                tablero[i + 1][j + 1] == jugador &&
                tablero[i + 2][j + 2] == jugador &&
                tablero[i + 3][j + 3] == jugador) {
                return true;
            }
        }
    }

    // Verificar en diagonal (de derecha a izquierda)
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 3; j < COLUMNAS; ++j) {
            if (tablero[i][j] == jugador &&
                tablero[i + 1][j - 1] == jugador &&
                tablero[i + 2][j - 2] == jugador &&
                tablero[i + 3][j - 3] == jugador) {
                return true;
            }
        }
    }

    return false;
    }

    bool esEmpate() const { 
        
        return tableroLleno() && !verificarGanador('X') && !verificarGanador('O');
    }
};
