#ifndef BITS_H
#define BITS_H
// Calcula cuántos bytes se requieren para almacenar 'filas x columnas' fichas de 3 bits
int calcularCantidadBytes(int filas, int columnas);

// Convierte (fila, columna) a un índice lineal (0, 1, 2, ...)
int calcularIndice(int fila, int columna, int columnas);

// Obtiene el valor de 3 bits de una ficha dada su posición (fila, columna)
unsigned char leerFicha(const unsigned char* tablero, int fila, int columna, int columnas);

// Escribe un valor de 3 bits (0 a 7) en la posición (fila, columna)
void escribirFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valor);
#endif // BITS_H
