#pragma once
#include <iostream>
#include "Tablero.h"
#include "Jugador.h"


using namespace std;

class JugadorHumano : public Jugador {
public:
    int hacerMovimiento(const Tablero& tablero) const override {
        int columna;
        do {
            cout << "Elige una columna (1-" << COLUMNAS  << "): ";
            cin >> columna;
        } while (!tablero.validarColumna(columna) || tablero.columnaLlena(columna));
        return columna;
    }
};
