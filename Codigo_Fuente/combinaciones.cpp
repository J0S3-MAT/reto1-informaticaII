#include "combinaciones.h"
#include "bits.h"

bool detectarYMarcarCombinaciones(unsigned char* tablero, int filas, int columnas) {
    bool hayCombinacion = false;

    // 1. Deteccion Horizontal
    for (int f = 0; f < filas; ++f) {
        int contador = 1;
        for (int c = 0; c < columnas - 1; ++c) {
            unsigned char actual = leerFicha(tablero, f, c, columnas);
            unsigned char siguiente = leerFicha(tablero, f, c + 1, columnas);

            // Si no son vacias ni marcadas y son iguales
            if (actual < 6 && actual == siguiente) {
                contador++;
            } else {
                if (contador >= 3) {
                    hayCombinacion = true;
                    // Marcar grupo con el valor 7
                    for (int k = 0; k < contador; ++k) {
                        escribirFicha(tablero, f, c - k, columnas, 7);
                    }
                }
                contador = 1;
            }
        }
        // Verificar el ultimo grupo al finalizar la fila
        if (contador >= 3) {
            hayCombinacion = true;
            for (int k = 0; k < contador; ++k) {
                escribirFicha(tablero, f, (columnas - 1) - k, columnas, 7);
            }
        }
    }

    // 2. Deteccion Vertical
    for (int c = 0; c < columnas; ++c) {
        int contador = 1;
        for (int f = 0; f < filas - 1; ++f) {
            unsigned char actual = leerFicha(tablero, f, c, columnas);
            unsigned char siguiente = leerFicha(tablero, f + 1, c, columnas);

            if (actual < 6 && actual == siguiente) {
                contador++;
            } else {
                if (contador >= 3) {
                    hayCombinacion = true;
                    for (int k = 0; k < contador; ++k) {
                        escribirFicha(tablero, f - k, c, columnas, 7);
                    }
                }
                contador = 1;
            }
        }
        if (contador >= 3) {
            hayCombinacion = true;
            for (int k = 0; k < contador; ++k) {
                escribirFicha(tablero, (filas - 1) - k, c, columnas, 7);
            }
        }
    }

    return hayCombinacion;
}

void eliminarMarcadas(unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            if (leerFicha(tablero, f, c, columnas) == 7) {
                escribirFicha(tablero, f, c, columnas, 6); // 6 representa espacio vacio '.'
            }
        }
    }
}