/*#include <iostream>
#include "bits.h"
#include "tablero.h"

using namespace std;

int main() {
    int filas = 4;
    int columnas = 4;
    int bytesNecesarios = calcularCantidadBytes(filas, columnas);

    // Reservar memoria e inicializar en 0
    unsigned char* tablero = new unsigned char[bytesNecesarios]();

    cout << "Filas: " << filas << ", Columnas: " << columnas << endl;
    cout << "Bytes reservados en el Heap: " << bytesNecesarios << endl;

    // Valores de prueba (0 a 7)
    unsigned char valoresPrueba[16] = {0, 1, 2, 3, 4, 5, 6, 7, 1, 3, 5, 7, 0, 2, 4, 6};

    // Llenar el tablero
    int k = 0;
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            escribirFicha(tablero, f, c, columnas, valoresPrueba[k++]);
        }
    }

    // 1. Mostrar vista numérica normal
    mostrarTablero(tablero, filas, columnas);

    // 2. Mostrar vista binaria
    mostrarTableroBinario(tablero, filas, columnas);

    // Liberar la memoria
    delete[] tablero;
    tablero = nullptr;

    return 0;
}*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // imprime caracteres

#include "bits.h"
#include "tablero.h"
#include "combinaciones.h"

using namespace std;

int main() {
    // Forzar la consola de Windows a interpretar caracteres UTF-8
    SetConsoleOutputCP(CP_UTF8);

    srand(time(nullptr));
    int filas = 4;
    int columnas = 4;

    unsigned char* tablero = crearTablero(filas, columnas);
    generarFichasAleatorias(tablero, filas, columnas);

    // Forzar combinacion de 3 corazones (0) en la fila 0
    escribirFicha(tablero, 0, 0, columnas, 0);
    escribirFicha(tablero, 0, 1, columnas, 0);
    escribirFicha(tablero, 0, 2, columnas, 0);

    cout << "--- TABLERO INICIAL ---";
    mostrarTablero(tablero, filas, columnas);

    if (detectarYMarcarCombinaciones(tablero, filas, columnas)) {
        cout << "--- COMBINACIONES MARCADAS (*) ---";
        mostrarTablero(tablero, filas, columnas);

        eliminarMarcadas(tablero, filas, columnas);
        cout << "--- FICHAS ELIMINADAS (.) ---";
        mostrarTablero(tablero, filas, columnas);
    }

    destruirTablero(tablero);
    return 0;
}