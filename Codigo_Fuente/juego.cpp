#include "juego.h"
#include "tablero.h"
#include "combinaciones.h"
#include "bits.h"
#include <iostream>
using namespace std;

bool leerEntero(const char* mensaje, int minimo, int maximo, int& resultado)
{
    char entrada[16];

    while(true)
    {
        cout << mensaje;

        if(!cin.getline(entrada, 16))
        {
            if(cin.eof())
                return false;

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Entrada invalida.\n";
            continue;
        }

        int numero = 0;
        int signo = 1;
        int i = 0;

        if(entrada[0] == '-')
        {
            signo = -1;
            i = 1;
        }

        bool valido = entrada[i] != '\0';

        while(entrada[i] != '\0' && valido)
        {
            if(entrada[i] < '0' || entrada[i] > '9')
            {
                valido = false;
            }
            else
            {
                numero = numero * 10 + (entrada[i] - '0');

                if(numero > MAX_DIMENSION)
                    valido = false;
            }

            i++;
        }

        numero *= signo;

        if(valido && numero >= minimo && numero <= maximo)
        {
            resultado = numero;
            return true;
        }

        cout << "Ingrese un numero entero valido.\n";
    }
}


int resolverCascadas(unsigned char* tablero,unsigned char* marcas,int filas,int columnas,int& cascadasTurno,int& combinacionesTurno)
{
    int totalEliminadasCascada = 0;

    cascadasTurno = 0;
    combinacionesTurno = 0;

    while(true)
    {
        limpiarMascaraCompacta(marcas, filas, columnas);

        int encontradas =
            detectarCombinacionesCompacta(tablero, marcas,
                                          filas, columnas);

        if(encontradas == 0)
        {
            break;
        }

        combinacionesTurno += encontradas;
        cascadasTurno++;

        totalEliminadasCascada +=
            eliminarMarcadasCompacta(tablero, marcas,
                                     filas, columnas);

        aplicarGravedad(tablero, filas, columnas);

        rellenarTablero(tablero, filas, columnas);
    }

    return totalEliminadasCascada;
}

bool eliminarSeleccion(unsigned char* tablero,int fila,int columna,int filas,int columnas)
{
    if(fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
    {
        return false;
    }


    unsigned char ficha = leerFicha(tablero,fila,columna,columnas);


    if(ficha == 6)
    {
        return false;
    }


    escribirFicha(tablero,fila,columna,columnas,6);


    return true;
}

bool procesarJugada(unsigned char* tablero, unsigned char* marcas, int fila, int columna, int filas, int columnas, int& eliminadasTurno, int& cascadasTurno, int& combinacionesTurno)
{
    if(!eliminarSeleccion(tablero, fila, columna, filas, columnas))
    {
        return false;
    }

    aplicarGravedad(tablero, filas, columnas);
    rellenarTablero(tablero, filas, columnas);

    // Pasamos combinacionesTurno al final
    int eliminadasPorCascada = resolverCascadas(tablero, marcas, filas, columnas, cascadasTurno, combinacionesTurno);

    eliminadasTurno = 1 + eliminadasPorCascada;

    return true;
}

void mostrarEstadoJuego(unsigned char* tablero,int filas,int columnas,int eliminadasTurno,int cascadasTurno,int combinacionesTurno,
int totalFichasEliminadas,
int totalCombinaciones,
int turnosUsuario,
int puntuacion)
{
    cout << "\n=== TABLERO ACTUAL ===\n";

    mostrarTablero(tablero, filas, columnas);
    mostrarTableroBinario(tablero, filas, columnas);

    if(eliminadasTurno > 0)
    {
        cout << "-> JUGADA ANTERIOR: Se eliminaron "
             << eliminadasTurno << " fichas.\n";

        cout << "-> CASCADAS PRODUCIDAS: "
             << cascadasTurno << "\n";

        cout << "-> COMBINACIONES DETECTADAS: "
             << combinacionesTurno << "\n";
    }

    cout << "-> TOTAL ACUMULADO: "
         << totalFichasEliminadas
         << " fichas y "
         << totalCombinaciones
         << " combinaciones.\n";

    cout << "-> ELIMINACIONES REALIZADAS POR EL USUARIO: "
         << turnosUsuario << "\n";

    cout << "-> PUNTUACION: "
         << puntuacion << "\n";

    cout << "-> DIMENSIONES: "
         << filas << "x" << columnas << "\n\n";
}

int pedirAccion(int filas, int columnas)
{
    int accion;

    cout << "Accion (-1 salir, -2 agr fila";

    if(filas > 1)
    {
        cout << ", -3 elim fila";
    }

    if(columnas > 1)
    {
        cout << ", -4 elim col";
    }

    cout << ", -5 agr col, Eliminar una ficha (indique el numero de fila donde esta)): ";

    if(!leerEntero("", -5, filas - 1, accion))
    {
        return -1;
    }

    return accion;
}

bool procesarModificacionTablero(int accion,unsigned char*& tablero,unsigned char*& marcas,int& filas,int& columnas,int& bytesReservados,
 int& eliminadasTurno,
 int& cascadasTurno,
 int& combinacionesTurno)
{
    int pos;

    // AGREGAR FILA
    if(accion == -2)
    {

        if(filas >= MAX_DIMENSION)
        {
            cout << "No se pueden agregar mas filas.\n";
            return true;
        }

        cout << "Posicion para la nueva fila (0 a "
             << filas << "): ";

        if(!leerEntero("", 0, filas, pos))
        {
            return true;
        }
        destruirMascaraCompacta(marcas);

        agregarFila(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascaraCompacta(filas, columnas);

        eliminadasTurno = resolverCascadas(tablero,marcas,filas,columnas,cascadasTurno,combinacionesTurno);

        cout << "Fila agregada.\n";

        return true;
    }

    // ELIMINAR FILA
    if(accion == -3)
    {
        if(filas <= 1)
        {
            cout << "Comando oculto/invalido.\n";
            return true;
        }

        cout << "Posicion de la fila a eliminar (0 a "
             << filas - 1 << "): ";

        if(!leerEntero("", 0, filas - 1, pos))
        {
            return true;
        }

        destruirMascaraCompacta(marcas);

        eliminarFila(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascaraCompacta(filas, columnas);

        eliminadasTurno = resolverCascadas(tablero,marcas,filas,columnas,cascadasTurno,combinacionesTurno);

        cout << "Fila eliminada.\n";

        return true;
    }

    // ELIMINAR COLUMNA
    if(accion == -4)
    {
        if(columnas <= 1)
        {
            cout << "Comando oculto/invalido.\n";
            return true;
        }

        cout << "Posicion de la columna a eliminar (0 a "
             << columnas - 1 << "): ";

        if(!leerEntero("", 0, columnas - 1, pos))
        {
            return true;
        }

        destruirMascaraCompacta(marcas);

        eliminarColumna(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascaraCompacta(filas, columnas);

        eliminadasTurno = resolverCascadas(tablero,marcas,filas,columnas,cascadasTurno,combinacionesTurno);

        cout << "Columna eliminada.\n";

        return true;
    }

    // AGREGAR COLUMNA
    if(accion == -5)
    {

        if(columnas >= MAX_DIMENSION)
        {
            cout << "No se pueden agregar mas columnas.\n";
            return true;
        }

        cout << "Posicion para la nueva columna (0 a "
             << columnas << "): ";

        if(!leerEntero("", 0, columnas, pos))
        {
            return true;
        }

        destruirMascaraCompacta(marcas);

        agregarColumna(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascaraCompacta(filas, columnas);

        eliminadasTurno = resolverCascadas(tablero,marcas,filas,columnas,cascadasTurno,combinacionesTurno);

        cout << "Columna agregada.\n";

        return true;
    }

    // No era un comando de modificacion
    return false;
}

void actualizarEstadisticas(int eliminadasTurno,int cascadasTurno,int combinacionesTurno,int& totalFichasEliminadas,int& totalCombinaciones,
int& turnosUsuario,
int& puntuacion,
bool esJugadaUsuario)
{
    totalFichasEliminadas += eliminadasTurno;

    totalCombinaciones += combinacionesTurno;

    if(esJugadaUsuario)
    {
        turnosUsuario++;
    }

    puntuacion += eliminadasTurno + (combinacionesTurno * 10);
}


void ejecutarJugadaUsuario(unsigned char* tablero,unsigned char* marcas,int filaSeleccionada,int filas,int columnas,int& eliminadasTurno,int& cascadasTurno,
int& combinacionesTurno,int& totalFichasEliminadas,int& totalCombinaciones,int& turnosUsuario,int& puntuacion)
{
    int columna;

    if(!leerEntero("Columna: ", 0, columnas - 1, columna))
    {
        return;
    }

    if(procesarJugada(tablero,marcas,filaSeleccionada,columna,filas,columnas,eliminadasTurno,cascadasTurno,combinacionesTurno))
    {
        cout << "Jugada realizada\n";

        actualizarEstadisticas(eliminadasTurno,cascadasTurno,combinacionesTurno,totalFichasEliminadas,totalCombinaciones,turnosUsuario,puntuacion,true);
    }
    else
    {
        cout << "Movimiento invalido\n";

        eliminadasTurno = 0;
        cascadasTurno = 0;
        combinacionesTurno = 0;
    }
}

int inicializarJuego(unsigned char*& tablero,unsigned char*& marcas,int filas,int columnas)
{
    tablero = crearTablero(filas, columnas);
    marcas = crearMascaraCompacta(filas, columnas);

    generarFichasAleatorias(tablero, filas, columnas);

    int cascadasIniciales = 0;
    int combinacionesIniciales = 0;

    resolverCascadas(tablero,marcas,filas,columnas,cascadasIniciales,combinacionesIniciales);

    return calcularCantidadBytes(filas, columnas);
}



bool pedirDimensiones(int& filas, int& columnas)
{
    if(!leerEntero("Cantidad de filas (1 a 40): ",
                    1, MAX_DIMENSION, filas))
    {
        return false;
    }

    return leerEntero("Cantidad de columnas (1 a 40): ",
                      1, MAX_DIMENSION, columnas);
}