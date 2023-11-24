#include <iostream>
#include <vector>
#include <climits>

const int FILAS = 6;
const int COLUMNAS = 7;

bool columnaLlena(const std::vector<std::vector<char>>& tablero, int columna) {
    return tablero[0][columna] != ' ';
}

bool tableroLleno(const std::vector<std::vector<char>>& tablero) {
    for (int columna = 0; columna < COLUMNAS; ++columna) {
        if (!columnaLlena(tablero, columna)) {
            return false;
        }
    }
    return true;
}

void deshacerMovimiento(std::vector<std::vector<char>>& tablero, int columna) {
    for (int i = 0; i < FILAS; ++i) {
        if (tablero[i][columna] != ' ') {
            tablero[i][columna] = ' ';
            break;
        }
    }
}

void imprimirTablero(const std::vector<std::vector<char>>& tablero) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << tablero[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool validarColumna(int columna) {
    return columna >= 0 && columna < COLUMNAS;
}

bool verificarGanadorEnLinea(const std::vector<char>& linea, char jugador) {
    for (int i = 0; i <= COLUMNAS - 4; ++i) {
        if (linea[i] == jugador && linea[i + 1] == jugador && linea[i + 2] == jugador && linea[i + 3] == jugador) {
            return true;
        }
    }
    return false;
}

bool verificarGanador(const std::vector<std::vector<char>>& tablero, char jugador) {
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

int evaluarTablero(const std::vector<std::vector<char>>& tablero, char jugador) {
    // Implementa una función de evaluación más sofisticada según tus necesidades.
    if (verificarGanador(tablero, jugador)) {
        return (jugador == 'X') ? 1 : -1;
    } else {
        return 0;
    }
}

bool esTerminal(const std::vector<std::vector<char>>& tablero) {
    // Implementa la función esTerminal según tus reglas específicas de finalización.
    return verificarGanador(tablero, 'X') || verificarGanador(tablero, 'O') || tableroLleno(tablero);
}

void colocarFicha(std::vector<std::vector<char>>& tablero, int columna, char jugador) {
    for (int i = FILAS - 1; i >= 0; --i) {
        if (tablero[i][columna] == ' ') {
            tablero[i][columna] = jugador;
            break;
        }
    }
}

int minimax(std::vector<std::vector<char>>& tablero, int profundidad, int alfa, int beta, bool esMaximizador) {
    if (profundidad == 0 || esTerminal(tablero)) {
        return evaluarTablero(tablero, 'X');
    }

    if (esMaximizador) {
        int mejorValor = INT_MIN;
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            if (!columnaLlena(tablero, columna)) {
                colocarFicha(tablero, columna, 'X');
                mejorValor = std::max(mejorValor, minimax(tablero, profundidad - 1, alfa, beta, false));
                alfa = std::max(alfa, mejorValor);
                deshacerMovimiento(tablero, columna);
                if (beta <= alfa) {
                    break;  // Poda alfa-beta
                }
            }
        }
        return mejorValor;
    } else {
        int mejorValor = INT_MAX;
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            if (!columnaLlena(tablero, columna)) {
                colocarFicha(tablero, columna, 'O');
                mejorValor = std::min(mejorValor, minimax(tablero, profundidad - 1, alfa, beta, true));
                beta = std::min(beta, mejorValor);
                deshacerMovimiento(tablero, columna);
                if (beta <= alfa) {
                    break;  // Poda alfa-beta
                }
            }
        }
        return mejorValor;
    }
}

int encontrarMejorMovimiento(std::vector<std::vector<char>>& tablero) {
    int mejorValor = INT_MIN;
    int mejorColumna = -1;

    for (int columna = 0; columna < COLUMNAS; ++columna) {
        if (!columnaLlena(tablero, columna)) {
            colocarFicha(tablero, columna, 'X');
            int valorMovimiento = minimax(tablero, 5, INT_MIN, INT_MAX, false); // Profundidad 4 arbitraria
            deshacerMovimiento(tablero, columna);

            if (valorMovimiento > mejorValor) {
                mejorValor = valorMovimiento;
                mejorColumna = columna;
            }
        }
    }

    return mejorColumna;
}

int main() {
    std::vector<std::vector<char>> tablero(FILAS, std::vector<char>(COLUMNAS, ' '));
    char jugadorActual = 'X';

    while (!tableroLleno(tablero) && !verificarGanador(tablero, 'X') && !verificarGanador(tablero, 'O')) {
    if (jugadorActual == 'X') {
        // Jugador humano
        imprimirTablero(tablero);
        int columna;
        do {
            std::cout << "Jugador " << jugadorActual << ", elige una columna (0-" << COLUMNAS - 1 << "): ";
            std::cin >> columna;
        } while (!validarColumna(columna) || columnaLlena(tablero, columna));
        colocarFicha(tablero, columna, jugadorActual);
    } else {
        // Jugador AI (Minimax con poda alfa-beta)
        int mejorColumna = encontrarMejorMovimiento(tablero);
        std::cout << "La IA elige la columna: " << mejorColumna << std::endl;
        colocarFicha(tablero, mejorColumna, jugadorActual);
    }

    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
}

imprimirTablero(tablero);

if (verificarGanador(tablero, 'X')) {
    std::cout << "¡Jugador X ha ganado!\n";
} else if (verificarGanador(tablero, 'O')) {
    std::cout << "¡Jugador O ha ganado!\n";
} else {
    std::cout << "¡Empate!\n";
}
}



