#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Detecta combinaciones horizontales y verticales, y marca las fichas involucradas con el valor 7
bool detectarCombinaciones(unsigned char* tablero, bool** marcas,int filas,int columnas);

// Reemplaza las fichas marcadas (7) por espacio vacio (6)
void eliminarMarcadas(unsigned char* tablero, bool** marcas, int filas,int columnas);

bool** crearMascara(int filas, int columnas);

// ------------TEMPORAL -----------
void imprimirMascara(bool** marcas, int filas, int columnas);

void aplicarGravedad(unsigned char* tablero,int filas,int columnas);

void limpiarMascara(bool** marcas, int filas, int columnas);

#endif // COMBINACIONES_H
