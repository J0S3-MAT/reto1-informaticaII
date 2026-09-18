#include <iostream>
#include <cstdlib>
#include "tablero.h"
#include "bits.h"
#include <iomanip>

using namespace std;

unsigned char* crearTablero(int filas, int columnas) {
    int bytes = calcularCantidadBytes(filas, columnas);
    return new unsigned char[bytes]();
}

void destruirTablero(unsigned char*& tablero) {
    if (tablero != nullptr) {
        delete[] tablero;
        tablero = nullptr;
    }
}

void generarFichasAleatorias(unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            unsigned char ficha = rand() % 6;
            escribirFicha(tablero, f, c, columnas, ficha);
        }
    }
}

void imprimirFichaBinaria(unsigned char ficha) {
    for (int i = 2; i >= 0; --i) {
        cout << ((ficha >> i) & 1);
    }
}

void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas) {
    cout << "\n=== TABLERO EN FORMATO BINARIO (3 bits) ===\n";
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            unsigned char ficha = leerFicha(tablero, f, c, columnas);
            imprimirFichaBinaria(ficha);
            cout << " ";
        }
        cout << "\n";
    }
    cout << "===========================================\n\n";
}



void mostrarTablero(const unsigned char* tablero, int filas, int columnas)
{
    const char simbolos[7] = {'@', '#', '$', '%', '&', '+', '.'};

    cout << "\n=== TABLERO SWEET CRUSH ===\n";

    // Encabezado de columnas
    cout << "   ";

    for(int c = 0; c < columnas; c++)
    {
        cout << setw(3) << c;
    }

    cout << "\n";

    // Imprimir las filas y las fichas
    for(int f = 0; f < filas; f++)
    {
        cout << setw(2) << f << " ";

        for(int c = 0; c < columnas; c++)
        {
            unsigned char ficha = leerFicha(tablero, f, c, columnas);

            cout << setw(3) << simbolos[ficha];
        }

        cout << "\n";
    }

    cout << "============================\n\n";
}

void rellenarTablero(unsigned char* tablero,int filas,int columnas)
{
    for(int c = 0; c < columnas; c++)
    {
        for(int f = 0; f < filas; f++)
        {
            unsigned char valor =leerFicha(tablero,f,c,columnas);

            if(valor == 6)
            {
                unsigned char nuevaFicha = rand() % 6;

                escribirFicha(tablero,f,c,columnas,nuevaFicha);
            }
        }
    }
}

void agregarFila(unsigned char*& tablero, int& filas, int columnas,
                 int posicion, int& bytesReservados)
{
    int filasNuevas = filas + 1;

    int bytesNecesarios = calcularCantidadBytes(filasNuevas, columnas);

    unsigned char* nuevoTablero = crearTablero(filasNuevas, columnas);

    // Copiar las fichas anteriores
    for(int f = 0; f < filas; f++)
    {
        for(int c = 0; c < columnas; c++)
        {
            unsigned char ficha = leerFicha(tablero, f, c, columnas);

            int nuevaFila;

            if(f < posicion)
            {
                nuevaFila = f;
            }
            else
            {
                nuevaFila = f + 1;
            }

            escribirFicha(nuevoTablero, nuevaFila, c, columnas, ficha);
        }
    }

    // Generar las fichas de la nueva fila
    for(int c = 0; c < columnas; c++)
    {
        unsigned char ficha = rand() % 6;

        escribirFicha(nuevoTablero, posicion, c, columnas, ficha);
    }

    destruirTablero(tablero);

    tablero = nuevoTablero;

    filas = filasNuevas;

    bytesReservados = bytesNecesarios;
}

void eliminarFila(unsigned char*& tablero, int& filas, int columnas, int posicion, int& bytesReservados)
{
    int filasNuevas = filas - 1;
    int bytesNecesarios = calcularCantidadBytes(filasNuevas, columnas);
    double utilizacion = (double)bytesNecesarios / bytesReservados;
    bool reducirMemoria = utilizacion < 0.65;

    if(reducirMemoria)
    {
        unsigned char* nuevoTablero = crearTablero(filasNuevas, columnas);

        for(int f = 0; f < filas; f++)
        {
            if(f == posicion) continue;

            int nuevaFila;
            if(f < posicion)
            {
                nuevaFila = f;
            }
            else
            {
                nuevaFila = f - 1;
            }

            for(int c = 0; c < columnas; c++)
            {
                unsigned char ficha = leerFicha(tablero, f, c, columnas);
                escribirFicha(nuevoTablero, nuevaFila, c, columnas, ficha);
            }
        }

        destruirTablero(tablero);
        tablero = nuevoTablero;
        bytesReservados = bytesNecesarios;
    }
    else
    {
        for(int f = posicion; f < filas - 1; f++)
        {
            for(int c = 0; c < columnas; c++)
            {
                unsigned char ficha = leerFicha(tablero, f + 1, c, columnas);
                escribirFicha(tablero, f, c, columnas, ficha);
            }
        }
    }

    filas = filasNuevas;
}

void agregarColumna(unsigned char*& tablero, int filas, int& columnas, int posicion, int& bytesReservados)
{
    int columnasNuevas = columnas + 1;
    int bytesNecesarios = calcularCantidadBytes(filas, columnasNuevas);
    unsigned char* nuevoTablero = crearTablero(filas, columnasNuevas);

    // Copiar las columnas actuales
    for(int f = 0; f < filas; f++)
    {
        for(int c = 0; c < columnas; c++)
        {
            unsigned char ficha = leerFicha(tablero, f, c, columnas);
            int nuevaColumna;

            if(c < posicion)
                nuevaColumna = c;
            else
                nuevaColumna = c + 1;

            escribirFicha(nuevoTablero, f, nuevaColumna, columnasNuevas, ficha);
        }
    }

    // Llenar la nueva columna
    for(int f = 0; f < filas; f++)
    {
        unsigned char ficha = rand() % 6;
        escribirFicha(nuevoTablero, f, posicion, columnasNuevas, ficha);
    }

    destruirTablero(tablero);
    tablero = nuevoTablero;
    columnas = columnasNuevas;
    bytesReservados = bytesNecesarios;
}

void eliminarColumna(unsigned char*& tablero, int filas, int& columnas, int posicion, int& bytesReservados)
{
    int columnasNuevas = columnas - 1;
    int bytesNecesarios = calcularCantidadBytes(filas, columnasNuevas);
    double utilizacion = (double)bytesNecesarios / bytesReservados;
    bool reducirMemoria = utilizacion < 0.65;

    if(reducirMemoria)
    {
        unsigned char* nuevoTablero = crearTablero(filas, columnasNuevas);

        for(int f = 0; f < filas; f++)
        {
            for(int c = 0; c < columnas; c++)
            {
                if(c == posicion)
                    continue;

                int nuevaColumna;
                if(c < posicion)
                    nuevaColumna = c;
                else
                    nuevaColumna = c - 1;

                unsigned char ficha = leerFicha(tablero, f, c, columnas);
                escribirFicha(nuevoTablero, f, nuevaColumna, columnasNuevas, ficha);
            }
        }

        destruirTablero(tablero);
        tablero = nuevoTablero;
        bytesReservados = bytesNecesarios;
    }
    else
    {
        // Reempaquetado in-situ seguro
        for(int f = 0; f < filas; f++)
        {
            for(int c = 0; c < columnas; c++)
            {
                if(c == posicion)
                    continue;

                int nuevaColumna;
                if(c < posicion)
                    nuevaColumna = c;
                else
                    nuevaColumna = c - 1;

                unsigned char ficha = leerFicha(tablero, f, c, columnas);
                escribirFicha(tablero, f, nuevaColumna, columnasNuevas, ficha);
            }
        }
    }

    columnas = columnasNuevas;
}