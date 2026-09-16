#ifndef TABLERO_H
#define TABLERO_H

unsigned char* crearTablero(int filas, int columnas);
void destruirTablero(unsigned char*& tablero);
void generarFichasAleatorias(unsigned char* tablero, int filas, int columnas);
void imprimirFichaBinaria(unsigned char ficha);
void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas);
void mostrarTablero(const unsigned char* tablero, int filas, int columnas);
void rellenarTablero(unsigned char* tablero,int filas,int columnas);


void agregarFila(unsigned char*& tablero, int& filas, int columnas,int posicion, int& bytesReservados);
void eliminarFila(unsigned char*& tablero, int& filas, int columnas, int posicion, int& bytesReservados);
void agregarColumna(unsigned char*& tablero, int filas, int& columnas, int posicion, int& bytesReservados);
void eliminarColumna(unsigned char*& tablero, int filas, int& columnas, int posicion, int& bytesReservados);
#endif // TABLERO_H