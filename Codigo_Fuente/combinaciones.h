#ifndef COMBINACIONES_H
#define COMBINACIONES_H

void aplicarGravedad(unsigned char* tablero,int filas,int columnas);

void marcarPosicion(unsigned char* marcas,int fila,int columna,int columnas);

bool estaMarcada(const unsigned char* marcas,int fila,int columna,int columnas);

unsigned char* crearMascaraCompacta(int filas, int columnas);

void limpiarMascaraCompacta(unsigned char* marcas,int filas,int columnas);

void destruirMascaraCompacta(unsigned char*& marcas);

int detectarCombinacionesCompacta(unsigned char* tablero,unsigned char* marcas,int filas,int columnas);

int eliminarMarcadasCompacta(unsigned char* tablero,const unsigned char* marcas,int filas,int columnas);
#endif // COMBINACIONES_H
