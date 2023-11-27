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
    int opcion;
    JugadorHumano jugador1;
    JugadorAI jugador2;

    cout << "Bienvenido a Conecta4\n";
    cout << "Seleccione el nivel de dificultad para la IA:\n";
    cout << "1. Facil\n";
    cout << "2. Medio\n";
    cout << "3. Dificil\n";
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            jugador2.setProfundidadMinimax(3);  // Nivel fácil
            jugador2.setProfundidadMax(3);  // Profundidad máxima para el nivel fácil
            break;
        case 2:
            jugador2.setProfundidadMinimax(20);  // Nivel medio
            jugador2.setProfundidadMax(20);  // Profundidad máxima para el nivel medio
            break;
        case 3:
            jugador2.setProfundidadMinimax(100);  // Nivel difícil
            jugador2.setProfundidadMax(100);  // Profundidad máxima para el nivel difícil
            break;
        default:
            cout << "Opcion no valida. Se seleccionara el nivel medio por defecto.\n";
            jugador2.setProfundidadMinimax(20);
            jugador2.setProfundidadMax(20);
            break;
    }

    Juego juego(&jugador1, &jugador2);
    juego.jugar();

    return 0;
}