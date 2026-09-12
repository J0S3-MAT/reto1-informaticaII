#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Detecta combinaciones horizontales y verticales, y marca las fichas involucradas con el valor 7
bool detectarYMarcarCombinaciones(unsigned char* tablero, int filas, int columnas);

// Reemplaza las fichas marcadas (7) por espacio vacio (6)
void eliminarMarcadas(unsigned char* tablero, int filas, int columnas);

#endif // COMBINACIONES_H
