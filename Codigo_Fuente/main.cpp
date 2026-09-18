#include <cstdlib>
#include <ctime>

#include "juego.h"
#include "tablero.h"
#include "combinaciones.h"


using namespace std;

int main()
{
    srand(time(nullptr));

    int filas;
    int columnas;

    if(!pedirDimensiones(filas, columnas))
    {
        return 0;
    }

    unsigned char* tablero = nullptr;
    unsigned char* marcas = nullptr;

    int bytesReservados = inicializarJuego(tablero,marcas,filas,columnas);

    // Datos de entrada
    int accion;

    // Estadisticas de la ultima jugada
    int eliminadasTurno = 0;
    int cascadasTurno = 0;
    int combinacionesTurno = 0;

    // Estadisticas acumuladas
    int totalFichasEliminadas = 0;
    int totalCombinaciones = 0;
    int turnosUsuario = 0;
    int puntuacion = 0;


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
                actualizarEstadisticas(eliminadasTurno,cascadasTurno,combinacionesTurno,totalFichasEliminadas,totalCombinaciones,turnosUsuario,puntuacion, false);
            }

            continue;
        }

        ejecutarJugadaUsuario(tablero,marcas,accion,filas,columnas,eliminadasTurno,cascadasTurno,combinacionesTurno,totalFichasEliminadas,totalCombinaciones,turnosUsuario,
        puntuacion);


    }
    destruirTablero(tablero);
    destruirMascaraCompacta(marcas);

    return 0;
}