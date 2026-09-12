#include "combinaciones.h"
#include "bits.h"
#include <iostream>

using namespace std;

bool** crearMascara(int filas, int columnas)
{
    //Reservo memoria para un arreglo de punteros, cada uno apunta a una fila de buleanos
    bool** marcas = new bool*[filas];

    //Recorro esas filas para poner las columnas
    for(int f = 0; f < filas; f++)
    {
        //Para cada fila F reservo la memoria de cada columna
        marcas[f] = new bool[columnas];

        //Inicializo en false todo ya que no quiero falsos positivos al momento de detectar una secuencia
        for(int c = 0; c < columnas; c++)
        {
            marcas[f][c] = false;
        }
    }



    return marcas;
}

void limpiarMascara(bool** marcas, int filas, int columnas)
{
    for(int f = 0; f < filas; f++)
    {
        for(int c = 0; c < columnas; c++)
        {
            marcas[f][c] = false;
        }
    }
}

// -----------------TEMPORAL ------------------------
void imprimirMascara(bool** marcas, int filas, int columnas)
{
    for(int f = 0; f < filas; f++)
    {
        for(int c = 0; c < columnas; c++)
        {
            cout << marcas[f][c] << " ";
        }

        cout << endl;
    }
}

bool detectarCombinaciones(unsigned char* tablero, bool** marcas,int filas,int columnas) {
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
                    // Marcar fichas
                    for (int k = 0; k < contador; ++k) {
                        marcas[f][c-k] = true;;
                    }
                }
                contador = 1;
            }
        }
        // Verificar el ultimo grupo al finalizar la fila
        if (contador >= 3) {
            hayCombinacion = true;
            for (int k = 0; k < contador; ++k) {
                marcas[f][(columnas - 1) - k] = true;
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
                        marcas[f-k][c] = true;
                    }
                }
                contador = 1;
            }
        }
        if (contador >= 3) {
            hayCombinacion = true;
            for (int k = 0; k < contador; ++k) {
                marcas[(filas - 1) - k][c] = true;
            }
        }
    }

    return hayCombinacion;
}

void eliminarMarcadas(unsigned char* tablero, bool** marcas, int filas,int columnas)
{
    for(int f = 0; f < filas; f++)
    {
        for(int c = 0; c < columnas; c++)
        {
            if(marcas[f][c])
            {
                escribirFicha(tablero, f, c, columnas, 6);
            }
        }
    }
}


void aplicarGravedad(unsigned char* tablero,int filas,int columnas)
{
    for(int c = 0; c < columnas; c++)
    {
        int destino = filas - 1; //Si tengo Fila 0, fila1, fila2, fila3
                                 //La fila del fondo es la fila 3, osea 4 -1
                                 //Necesario para empezar a recorrer las columas desde abajo

        for(int f = filas-1; f >= 0; f--)
        {
            unsigned char valor =leerFicha(tablero,f,c,columnas);


            //Solo escribo en cada casilla si es una ficha valida, si es un espacio no hago nada
            if(valor != 6)
            {
                escribirFicha(tablero,destino,c,columnas, valor);

                destino--;
            }
        }

            //Reemplazo las posiciones de arriba con vacios
        for(int f = 0; f <= destino; f++)
        {
            escribirFicha(tablero,f,c,columnas,6);
        }
    }
}
