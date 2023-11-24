#include <iostream>
#include <vector>
#include <climits>
#include "Tablero.h"
#include "Jugador.h"
#include "JugadorIa.h"
#include "JugadorHumano.h"
#include "Conecta4.h"


using namespace std;  

int main() {
    JugadorHumano jugador1;
    JugadorAI jugador2;

    Juego juego(&jugador1, &jugador2);
    juego.jugar();

    return 0;
}