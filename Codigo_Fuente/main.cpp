#include <iostream>
#include <ctime>

#include "juego.h"
#include "tablero.h"
#include "combinaciones.h"
#include "bits.h"

using namespace std;

int main()
{
    srand(time(nullptr));

    int filas = 4;
    int columnas = 4;

    unsigned char* tablero = crearTablero(filas, columnas);
    bool** marcas = crearMascara(filas, columnas);

    generarFichasAleatorias(tablero, filas, columnas);

    int cascadasIniciales = 0;
    int combinacionesIniciales = 0;

    resolverCascadas(tablero,marcas,filas,columnas,cascadasIniciales,combinacionesIniciales);

    // Datos de entrada
    int accion;
    int columna;

    // Estadisticas de la ultima jugada
    int eliminadasTurno = 0;
    int cascadasTurno = 0;
    int combinacionesTurno = 0;

    // Estadisticas acumuladas
    int totalFichasEliminadas = 0;
    int totalCombinaciones = 0;
    int turnosUsuario = 0;
    int puntuacion = 0;

    // Cantidad real de memoria reservada para el tablero
    int bytesReservados = calcularCantidadBytes(filas, columnas);

    while(true)
    {
        mostrarEstadoJuego(tablero,filas,columnas,eliminadasTurno,cascadasTurno,combinacionesTurno,totalFichasEliminadas,totalCombinaciones,turnosUsuario,puntuacion);

        accion = pedirAccion(filas, columnas);

        if(accion == -1)
        {
            break;
        }

        if(procesarModificacionTablero(accion,tablero,marcas,filas,columnas,bytesReservados,eliminadasTurno,cascadasTurno,combinacionesTurno))
        {
            if(eliminadasTurno > 0)
            {
                actualizarEstadisticas(eliminadasTurno,cascadasTurno,combinacionesTurno,totalFichasEliminadas,totalCombinaciones,turnosUsuario,puntuacion);
            }

            continue;
        }

        // =========================
        // JUGADA NORMAL
        // =========================

        cout << "Columna: ";
        cin >> columna;

        if(procesarJugada(tablero,marcas,accion,columna,filas,columnas,eliminadasTurno,cascadasTurno,combinacionesTurno))
        {
            cout << "Jugada realizada\n";

            actualizarEstadisticas(eliminadasTurno,cascadasTurno,combinacionesTurno,totalFichasEliminadas,totalCombinaciones,turnosUsuario,puntuacion);
        }

        else
        {
            cout << "Movimiento invalido\n";

            eliminadasTurno = 0;
            cascadasTurno = 0;
            combinacionesTurno = 0;
        }
    }

    destruirTablero(tablero);
    destruirMascara(marcas, filas);

    return 0;
}