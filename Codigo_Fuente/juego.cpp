#include "juego.h"
#include "tablero.h"
#include "combinaciones.h"
#include "bits.h"
#include <iostream>
using namespace std;

int resolverCascadas(unsigned char* tablero, bool** marcas, int filas, int columnas, int& cascadasTurno, int& combinacionesTurno)
{
    int totalEliminadasCascada = 0;
    cascadasTurno = 0;
    combinacionesTurno = 0; // <-- Reiniciamos el contador al entrar

    while(true)
    {
        limpiarMascara(marcas, filas, columnas);

        // Atrapamos cuantas combinaciones se formaron
        int encontradas = detectarCombinaciones(tablero, marcas, filas, columnas);

        if(encontradas == 0) // Si es 0, no hubo combinaciones
        {
            break;
        }

        combinacionesTurno += encontradas; // <-- Sumamos las combinaciones
        cascadasTurno++;

        totalEliminadasCascada += eliminarMarcadas(tablero, marcas, filas, columnas);

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

bool procesarJugada(unsigned char* tablero, bool** marcas, int fila, int columna, int filas, int columnas, int& eliminadasTurno, int& cascadasTurno, int& combinacionesTurno)
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

    cout << ", -5 agr col, o Fila): ";

    cin >> accion;

    return accion;
}

bool procesarModificacionTablero(int accion,unsigned char*& tablero,bool**& marcas,int& filas,int& columnas,int& bytesReservados,
 int& eliminadasTurno,
 int& cascadasTurno,
 int& combinacionesTurno)
{
    int pos;

    // AGREGAR FILA
    if(accion == -2)
    {
        cout << "Posicion para la nueva fila (0 a "
             << filas << "): ";

        cin >> pos;

        if(pos < 0 || pos > filas)
        {
            cout << "Posicion invalida.\n";
            return true;
        }

        destruirMascara(marcas, filas);

        agregarFila(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascara(filas, columnas);

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

        cin >> pos;

        if(pos < 0 || pos >= filas)
        {
            cout << "Posicion invalida.\n";
            return true;
        }

        destruirMascara(marcas, filas);

        eliminarFila(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascara(filas, columnas);

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

        cin >> pos;

        if(pos < 0 || pos >= columnas)
        {
            cout << "Posicion invalida.\n";
            return true;
        }

        destruirMascara(marcas, filas);

        eliminarColumna(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascara(filas, columnas);

        eliminadasTurno = resolverCascadas(tablero,marcas,filas,columnas,cascadasTurno,combinacionesTurno);

        cout << "Columna eliminada.\n";

        return true;
    }

    // AGREGAR COLUMNA
    if(accion == -5)
    {
        cout << "Posicion para la nueva columna (0 a "
             << columnas << "): ";

        cin >> pos;

        if(pos < 0 || pos > columnas)
        {
            cout << "Posicion invalida.\n";
            return true;
        }

        destruirMascara(marcas, filas);

        agregarColumna(tablero,filas,columnas,pos,bytesReservados);

        marcas = crearMascara(filas, columnas);

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

    puntuacion += eliminadasTurno + (cascadasTurno * 10);
}


void ejecutarJugadaUsuario(unsigned char* tablero,bool** marcas,int filaSeleccionada,int filas,int columnas,int& eliminadasTurno,int& cascadasTurno,
int& combinacionesTurno,int& totalFichasEliminadas,int& totalCombinaciones,int& turnosUsuario,int& puntuacion)
{
    int columna;

    cout << "Columna: ";
    cin >> columna;

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

int inicializarJuego(unsigned char*& tablero,bool**& marcas,int filas,int columnas)
{
    tablero = crearTablero(filas, columnas);
    marcas = crearMascara(filas, columnas);

    generarFichasAleatorias(tablero, filas, columnas);

    int cascadasIniciales = 0;
    int combinacionesIniciales = 0;

    resolverCascadas(tablero,marcas,filas,columnas,cascadasIniciales,combinacionesIniciales);

    return calcularCantidadBytes(filas, columnas);
}

void pedirDimensiones(int& filas, int& columnas)
{
    cout << "Cantidad de filas: ";
    cin >> filas;

    while(filas <= 0)
    {
        cout << "Valor invalido. Ingrese una cantidad de filas mayor que 0: ";
        cin >> filas;
    }

    cout << "Cantidad de columnas: ";
    cin >> columnas;

    while(columnas <= 0)
    {
        cout << "Valor invalido. Ingrese una cantidad de columnas mayor que 0: ";
        cin >> columnas;
    }
}