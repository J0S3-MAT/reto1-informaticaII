#include "juego.h"
#include "tablero.h"
#include "combinaciones.h"


void resolverCascadas(unsigned char* tablero,bool** marcas,int filas,int columnas)
{
    while(true)
    {
        limpiarMascara(marcas, filas, columnas);

        bool hayCombinacion =detectarCombinaciones(tablero,marcas,filas,columnas);


        if(!hayCombinacion)
            {
                break;
            }

        eliminarMarcadas(tablero,marcas,filas,columnas);

        aplicarGravedad(tablero,filas,columnas);

        rellenarTablero(tablero,filas,columnas);
        }
}