#pragma once
#include <iostream>
#include <vector>

using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;

class JugadorAI;

class Tablero {
friend class JugadorAI;
private:
    
    vector<vector<char>> tablero;
    int contarFichasEnLinea(const vector<char>& linea, char jugador) const {
        int contador = 0;
        for (char ficha : linea) {
            if (ficha == jugador) {
                contador++;
            }
        }
        return (contador == linea.size() - 1) ? 1 : 0;  // Penalizar solo si hay exactamente una ficha vacía en la línea
    }
    

public:
    Tablero() : tablero(FILAS, vector<char>(COLUMNAS, ' ')) {}
    
    
    bool columnaLlena(int columna) const {
    for (int i = 0; i < FILAS; ++i) {
        if (tablero[i][columna] == ' ') {
            return false;  // Si hay al menos una celda vacía, la columna no está llena
        }
    }
    return true;  // Si no se encontraron celdas vacías, la columna está llena
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
        for (int i = FILAS - 1; i >= 0; --i) {
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
        if (!validarColumna(columna)) {
            cout << "Columna no válida\n";
            return false;
        }

        // Verificar si la columna está llena
        if (columnaLlena(columna)) {
            cout << "Columna llena, no se puede colocar la ficha en la columna " << columna << "\n";
            return false;
        }

        // Buscar la posición para colocar la ficha
        for (int i = FILAS - 1; i >= 0; --i) {
            if (tablero[i][columna] == ' ') {
                tablero[i][columna] = jugador;
                cout << "Ficha colocada en fila " << i << ", columna " << columna << "\n";
                return true;  // Ficha colocada exitosamente
            }
        }

        // Este código no debería alcanzarse, pero se incluye como precaución
        cout << "Error al colocar la ficha en la columna " << columna << "\n";
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
            if (verificarLinea({tablero[i][j], tablero[i][j + 1], tablero[i][j + 2], tablero[i][j + 3]}, jugador)) {
                return true;
            }
        }
    }

    // Verificar en vertical
    for (int j = 0; j < COLUMNAS; ++j) {
        for (int i = 0; i <= FILAS - 4; ++i) {
            if (verificarLinea({tablero[i][j], tablero[i + 1][j], tablero[i + 2][j], tablero[i + 3][j]}, jugador)) {
                return true;
            }
        }
    }

    // Verificar en diagonal
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (verificarLinea({tablero[i][j], tablero[i + 1][j + 1], tablero[i + 2][j + 2], tablero[i + 3][j + 3]}, jugador)) {
                return true;
            }
        }
    }

    // Verificar en diagonal (de derecha a izquierda)
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 3; j < COLUMNAS; ++j) {
            if (verificarLinea({tablero[i][j], tablero[i + 1][j - 1], tablero[i + 2][j - 2], tablero[i + 3][j - 3]}, jugador)) {
                return true;
            }
        }
    }

    return false;
    }

    bool esEmpate() const { 
        
        return tableroLleno() && !verificarGanador('X') && !verificarGanador('O');
    }

    bool verificarLinea(const vector<char>& linea, char jugador) const {
        for (int i = 0; i <= 4; ++i) {
            if (linea[i] == jugador && linea[i + 1] == jugador && linea[i + 2] == jugador && linea[i + 3] == jugador) {
                return true;
            }
        }
        return false;
    }
    int evaluarFichasEnLinea(char jugador, int cantidad) const {
        int valor = 0;

        // Verificar en horizontal
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j <= COLUMNAS - cantidad; ++j) {
                vector<char> linea;
                for (int k = 0; k < cantidad; ++k) {
                    linea.push_back(tablero[i][j + k]);
                }
                valor += contarFichasEnLinea(linea, jugador);
            }
        }

        // Verificar en vertical
        for (int j = 0; j < COLUMNAS; ++j) {
            for (int i = 0; i <= FILAS - cantidad; ++i) {
                vector<char> linea;
                for (int k = 0; k < cantidad; ++k) {
                    linea.push_back(tablero[i + k][j]);
                }
                valor += contarFichasEnLinea(linea, jugador);
            }
        }

        // Verificar en diagonal
        for (int i = 0; i <= FILAS - cantidad; ++i) {
            for (int j = 0; j <= COLUMNAS - cantidad; ++j) {
                vector<char> diagonal;
                for (int k = 0; k < cantidad; ++k) {
                    diagonal.push_back(tablero[i + k][j + k]);
                }
                valor += contarFichasEnLinea(diagonal, jugador);
            }
        }

        // Verificar en diagonal (de derecha a izquierda)
        for (int i = 0; i <= FILAS - cantidad; ++i) {
            for (int j = cantidad - 1; j < COLUMNAS; ++j) {
                vector<char> diagonal;
                for (int k = 0; k < cantidad; ++k) {
                    diagonal.push_back(tablero[i + k][j - k]);
                }
                valor += contarFichasEnLinea(diagonal, jugador);
            }
        }

        return valor;
    }

    int evaluarPosicionFichas(char jugador) const {
        int valor = 0;

        // Ponderar las posiciones centrales del tablero
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                if (tablero[i][j] == jugador) {
                    valor += abs(j - COLUMNAS / 2);
                }
            }
        }

        return valor;
    }
};
