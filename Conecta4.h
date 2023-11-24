#pragma once
#include <iostream>
#include "Tablero.h"
#include "Jugador.h"

class Juego {
private:
    Tablero tablero;
    Jugador* jugadorX;
    Jugador* jugadorO;
    char jugadorActual;

public:
    Juego(Jugador* jugadorX, Jugador* jugadorO) : jugadorX(jugadorX), jugadorO(jugadorO), jugadorActual('X') {}

    void jugar() {
        while (!tablero.tableroLleno() && !tablero.verificarGanador('X') && !tablero.verificarGanador('O')) {
            tablero.imprimir();
            int columna = (jugadorActual == 'X') ? jugadorX->hacerMovimiento(tablero) : jugadorO->hacerMovimiento(tablero);

            if (tablero.validarColumna(columna) && !tablero.columnaLlena(columna)) {
                tablero.colocarFicha(columna, jugadorActual);
                jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            }
        }

        tablero.imprimir();

        if (tablero.verificarGanador('X')) {
            cout << "¡Jugador X ha ganado!\n";
        } else if (tablero.verificarGanador('O')) {
            cout << "¡Jugador O ha ganado!\n";
        } else {
            cout << "¡Empate!\n";
        }
    }
};