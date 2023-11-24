#pragma once
#include <iostream>
#include "Tablero.h"


using namespace std;


class Jugador {
public:
    virtual int hacerMovimiento(const Tablero& tablero) const = 0;
};