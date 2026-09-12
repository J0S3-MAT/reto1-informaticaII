#include <iostream>
#include <cstdlib>
#include "tablero.h"
#include "bits.h"

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

/*void mostrarTablero(const unsigned char* tablero, int filas, int columnas) {
    const char* simbolos[8] = {"♥", "♦", "♣", "♠", "★", "☼", ".", "*"};

    cout << "\n=== TABLERO SWEET CRUSH ===\n  ";
    for (int c = 0; c < columnas; ++c) cout << c << " ";
    cout << "\n";

    for (int f = 0; f < filas; ++f) {
        cout << f << " ";
        for (int c = 0; c < columnas; ++c) {
            unsigned char val = leerFicha(tablero, f, c, columnas);
            cout << simbolos[val] << " ";
        }
        cout << "\n";
    }
    cout << "============================\n\n";
}*/

void mostrarTablero(const unsigned char* tablero, int filas, int columnas) {
    // Simbolos ASCII estándar (nunca se dañan en consola)
    // 0=@, 1=#, 2=$, 3=%, 4=&, 5=+, 6=Vacio(.), 7=Marcado(*)
    const char* simbolos[8] = {"@", "#", "$", "%", "&", "+", ".", "*"};

    cout << "\n=== TABLERO SWEET CRUSH ===\n  ";
    for (int c = 0; c < columnas; ++c) cout << c << " ";
    cout << "\n";

    for (int f = 0; f < filas; ++f) {
        cout << f << " ";
        for (int c = 0; c < columnas; ++c) {
            unsigned char val = leerFicha(tablero, f, c, columnas);
            cout << simbolos[val] << " ";
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