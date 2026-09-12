#ifndef TABLERO_H
#define TABLERO_H

unsigned char* crearTablero(int filas, int columnas);
void destruirTablero(unsigned char*& tablero);
void generarFichasAleatorias(unsigned char* tablero, int filas, int columnas);
void imprimirFichaBinaria(unsigned char ficha);
void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas);
void mostrarTablero(const unsigned char* tablero, int filas, int columnas);
void rellenarTablero(unsigned char* tablero,int filas,int columnas);

#endif // TABLERO_H