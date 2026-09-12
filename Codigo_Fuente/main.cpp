#include <iostream>
#include "bits.h"
#include "tablero.h"
#include "combinaciones.h"
#include "juego.h"

using namespace std;


int main()
{
    int filas = 4;
    int columnas = 4;


    // Crear tablero
    unsigned char* tablero = crearTablero(filas, columnas);


    // Crear máscara de eliminaciones
    bool** marcas = crearMascara(filas, columnas);





    // Fila 0: A B C D
    escribirFicha(tablero,0,0,columnas,0);
    escribirFicha(tablero,0,1,columnas,1);
    escribirFicha(tablero,0,2,columnas,2);
    escribirFicha(tablero,0,3,columnas,3);


    // Fila 1: B C D E
    escribirFicha(tablero,1,0,columnas,1);
    escribirFicha(tablero,1,1,columnas,2);
    escribirFicha(tablero,1,2,columnas,3);
    escribirFicha(tablero,1,3,columnas,4);


    // Fila 2: B D E A
    escribirFicha(tablero,2,0,columnas,1);
    escribirFicha(tablero,2,1,columnas,3);
    escribirFicha(tablero,2,2,columnas,4);
    escribirFicha(tablero,2,3,columnas,0);


    // Fila 3: B A A E
    escribirFicha(tablero,3,0,columnas,1);
    escribirFicha(tablero,3,1,columnas,0);
    escribirFicha(tablero,3,2,columnas,0);
    escribirFicha(tablero,3,3,columnas,4);



    cout << "--- TABLERO INICIAL ---" << endl;

    mostrarTablero(tablero, filas, columnas);



    cout << endl;
    cout << "--- RESOLVIENDO CASCADAS ---" << endl;


    resolverCascadas(tablero,marcas,filas,columnas);



    cout << endl;
    cout << "--- TABLERO FINAL ---" << endl;

    mostrarTablero(tablero, filas, columnas);



    destruirTablero(tablero);

    return 0;
}