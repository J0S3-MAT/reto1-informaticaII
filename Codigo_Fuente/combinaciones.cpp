#include "combinaciones.h"
#include "bits.h"

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

void marcarPosicion(unsigned char* marcas,int fila,int columna,int columnas)
{
    int indice = calcularIndice(fila, columna, columnas);

    int byte = indice / 8;
    int bit = indice % 8;

    marcas[byte] |= (1 << bit);
}

bool estaMarcada(const unsigned char* marcas,int fila,int columna,int columnas)
{
    int indice = calcularIndice(fila, columna, columnas);

    int byte = indice / 8;
    int bit = indice % 8;

    return (marcas[byte] & (1 << bit)) != 0;
}

unsigned char* crearMascaraCompacta(int filas, int columnas)
{
    int totalBits = filas * columnas;

    int bytes = totalBits / 8;

    if(totalBits % 8 != 0)
    {
        bytes++;
    }

    return new unsigned char[bytes]();
}

void limpiarMascaraCompacta(unsigned char* marcas,int filas,int columnas)
{
    int totalBits = filas * columnas;

    int bytes = totalBits / 8;

    if(totalBits % 8 != 0)
    {
        bytes++;
    }

    for(int i = 0; i < bytes; i++)
    {
        marcas[i] = 0;
    }
}

void destruirMascaraCompacta(unsigned char*& marcas)
{
    delete[] marcas;

    marcas = nullptr;
}

int detectarCombinacionesCompacta(unsigned char* tablero,unsigned char* marcas,int filas,int columnas)
{
    int cantidadCombinaciones = 0;

    // DETECCION HORIZONTAL
    for(int f = 0; f < filas; f++)
    {
        int contador = 1;

        for(int c = 0; c < columnas - 1; c++)
        {
            unsigned char actual = leerFicha(tablero, f, c, columnas);
            unsigned char siguiente = leerFicha(tablero, f, c + 1, columnas);

            if(actual < 6 && actual == siguiente)
            {
                contador++;
            }
            else
            {
                if(contador >= 3)
                {
                    cantidadCombinaciones++;

                    for(int k = 0; k < contador; k++)
                    {
                        marcarPosicion(marcas, f, c - k, columnas);
                    }
                }

                contador = 1;
            }
        }

        // Combinacion al final de la fila
        if(contador >= 3)
        {
            cantidadCombinaciones++;

            for(int k = 0; k < contador; k++)
            {
                marcarPosicion(marcas, f, columnas - 1 - k, columnas);
            }
        }
    }

    // DETECCION VERTICAL
    for(int c = 0; c < columnas; c++)
    {
        int contador = 1;

        for(int f = 0; f < filas - 1; f++)
        {
            unsigned char actual = leerFicha(tablero, f, c, columnas);
            unsigned char siguiente = leerFicha(tablero, f + 1, c, columnas);

            if(actual < 6 && actual == siguiente)
            {
                contador++;
            }
            else
            {
                if(contador >= 3)
                {
                    cantidadCombinaciones++;

                    for(int k = 0; k < contador; k++)
                    {
                        marcarPosicion(marcas, f - k, c, columnas);
                    }
                }

                contador = 1;
            }
        }

        // Combinacion al final de la columna
        if(contador >= 3)
        {
            cantidadCombinaciones++;

            for(int k = 0; k < contador; k++)
            {
                marcarPosicion(marcas, filas - 1 - k, c, columnas);
            }
        }
    }

    return cantidadCombinaciones;
}

int eliminarMarcadasCompacta(unsigned char* tablero,const unsigned char* marcas,int filas,int columnas)
{
    int eliminadas = 0;

    for(int f = 0; f < filas; f++)
    {
        for(int c = 0; c < columnas; c++)
        {
            if(estaMarcada(marcas, f, c, columnas))
            {
                escribirFicha(tablero, f, c, columnas, 6);

                eliminadas++;
            }
        }
    }

    return eliminadas;
}