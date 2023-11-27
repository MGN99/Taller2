#pragma once
#include <iostream>
#include "Tablero.h"
#include "Jugador.h"
#include <chrono>



using namespace std;

class JugadorAI : public Jugador {
public:
    int getProfundidadMax() const;  
    void setProfundidadMax(int profundidad);  
    int hacerMovimiento(const Tablero& tablero) const override {
        auto inicio = std::chrono::high_resolution_clock::now();  // Guarda el tiempo de inicio

        int mejorColumna = (tablero, 5, INT_MIN, INT_MAX, true); // Profundidad 5 arbitraria

        auto fin = std::chrono::high_resolution_clock::now();  // Guarda el tiempo de fin
        auto duracion = std::chrono::duration_cast<std::chrono::seconds>(fin - inicio);  // Calcula la duración en segundos

        // Si el tiempo de duración supera el límite (por ejemplo, 5 segundos), utiliza la mejor columna actual
        if (duracion.count() >= 5) {
            std::cout << "¡Tiempo agotado! Se utilizará la mejor columna actual.\n";
            return mejorColumna;
        }

        return mejorColumna;
    }
    
    
    int getProfundidadMinimax() const;  // Getter para profundidadMinimax
    void setProfundidadMinimax(int profundidadMinimax);  
    

private:
    int profundidadMax;
    int profundidadMinimax;
    int minimax(const Tablero& tablero, int profundidad, int alfa, int beta, bool esMaximizador, char jugador) const {
    if (profundidad == 0 || tablero.verificarGanador('X') || tablero.verificarGanador('O') || tablero.tableroLleno()) {
        return evaluarTablero(tablero, jugador);
    }

    if (esMaximizador) {
        int mejorValor = INT_MIN;
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            if (!tablero.columnaLlena(columna)) {
                Tablero nuevoTablero = tablero; // Copia del tablero para simular el movimiento
                nuevoTablero.colocarFicha(columna, 'X');
                int valorMovimiento = minimax(nuevoTablero, profundidad - 1, alfa, beta, false, jugador);
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
                int valorMovimiento = minimax(nuevoTablero, profundidad - 1, alfa, beta, true, jugador);
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
    int valor = 0;

    // 1. Asignar valores basados en la cantidad de fichas en línea
    valor += tablero.evaluarFichasEnLinea(jugador, 1);  // 1 ficha en línea
    valor += tablero.evaluarFichasEnLinea(jugador, 2) * 10;  // 2 fichas en línea
    valor += tablero.evaluarFichasEnLinea(jugador, 3) * 100;  // 3 fichas en línea

    // 2. Considerar la posición de las fichas
    valor += tablero.evaluarPosicionFichas(jugador);

    // 3. Evitar posiciones perdedoras
    if (tablero.verificarGanador('O')) {
        // Penalizar posiciones que llevan a la victoria del oponente
        valor -= 1000;
    }

    return valor;
    }

    
};

int JugadorAI::getProfundidadMax() const {
    return profundidadMax;
};

void JugadorAI::setProfundidadMax(int profundidad) {
    profundidadMax = profundidad;
};

int JugadorAI::getProfundidadMinimax() const {
    return profundidadMinimax;
};

void JugadorAI::setProfundidadMinimax(int profundidad) {
    profundidadMinimax = profundidad;
};