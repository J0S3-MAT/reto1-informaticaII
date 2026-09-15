#ifndef JUEGO_H
#define JUEGO_H

int resolverCascadas(unsigned char* tablero, bool** marcas, int filas, int columnas, int& cascadasTurno, int& combinacionesTurno);

bool eliminarSeleccion(unsigned char* tablero, int fila, int columna, int filas, int columnas);

bool procesarJugada(unsigned char* tablero, bool** marcas, int fila, int columna, int filas, int columnas, int& eliminadasTurno, int& cascadasTurno, int& combinacionesTurno);

void mostrarEstadoJuego(unsigned char* tablero,int filas,int columnas,int eliminadasTurno,int cascadasTurno,int combinacionesTurno,int totalFichasEliminadas,int totalCombinaciones,int turnosUsuario,int puntuacion);

int pedirAccion(int filas, int columnas);

void actualizarEstadisticas(int eliminadasTurno,int cascadasTurno,int combinacionesTurno,int& totalFichasEliminadas,int& totalCombinaciones,
int& turnosUsuario,
int& puntuacion);

bool procesarModificacionTablero(int accion,unsigned char*& tablero,bool**& marcas,int& filas,int& columnas,int& bytesReservados,
int& eliminadasTurno,
int& cascadasTurno,
int& combinacionesTurno);
#endif // JUEGO_H