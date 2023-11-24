#pragma once
#include <iostream>
#include "Tablero.h"
#include "Jugador.h"


using namespace std;

class JugadorAI : public Jugador {
public:
    int hacerMovimiento(const Tablero& tablero) const override {
        // Selecciona la mejor columna usando el algoritmo Minimax con poda alfa-beta
        int mejorColumna = minimax(tablero, 5, INT_MIN, INT_MAX, true); // Profundidad 5 arbitraria
        return mejorColumna;
    }

private:
    int minimax(const Tablero& tablero, int profundidad, int alfa, int beta, bool esMaximizador) const {
        if (profundidad == 0 || tablero.verificarGanador('X') || tablero.verificarGanador('O') || tablero.tableroLleno()) {
            return evaluarTablero(tablero, 'X');
        }

        if (esMaximizador) {
            int mejorValor = INT_MIN;
            for (int columna = 0; columna < COLUMNAS; ++columna) {
                if (!tablero.columnaLlena(columna)) {
                    Tablero nuevoTablero = tablero; // Copia del tablero para simular el movimiento
                    nuevoTablero.colocarFicha(columna, 'X');
                    int valorMovimiento = minimax(nuevoTablero, profundidad - 1, alfa, beta, false);
                    mejorValor = max(mejorValor, valorMovimiento);
                    alfa = max(alfa, mejorValor);
                    if (beta <= alfa) {
                        break;  // Poda alfa-beta
                    }
                }
            }
            return mejorValor;
        } else {
            int mejorValor = INT_MAX;
            for (int columna = 0; columna < COLUMNAS; ++columna) {
                if (!tablero.columnaLlena(columna)) {
                    Tablero nuevoTablero = tablero; // Copia del tablero para simular el movimiento
                    nuevoTablero.colocarFicha(columna, 'O');
                    int valorMovimiento = minimax(nuevoTablero, profundidad - 1, alfa, beta, true);
                    mejorValor = min(mejorValor, valorMovimiento);
                    beta = min(beta, mejorValor);
                    if (beta <= alfa) {
                        break;  // Poda alfa-beta
                    }
                }
            }
            return mejorValor;
        }
    }

    int evaluarTablero(const Tablero& tablero, char jugador) const {
        // Implementa una función de evaluación más sofisticada según tus necesidades.
        // Por ejemplo, podrías asignar puntajes a diferentes situaciones en el tablero.
        if (tablero.verificarGanador(jugador)) {
            return (jugador == 'X') ? 1 : -1;
        } else {
            return 0;
        }
    }
};