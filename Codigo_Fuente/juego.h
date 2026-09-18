#ifndef JUEGO_H
#define JUEGO_H
const int MAX_DIMENSION = 40;

int resolverCascadas(unsigned char* tablero,unsigned char* marcas,int filas, int columnas,int& cascadasTurno,int& combinacionesTurno);

bool eliminarSeleccion(unsigned char* tablero, int fila, int columna, int filas, int columnas);

bool procesarJugada(unsigned char* tablero,unsigned char* marcas,int fila, int columna,int filas, int columnas,int& eliminadasTurno,int& cascadasTurno,int& combinacionesTurno);

void mostrarEstadoJuego(unsigned char* tablero,int filas,int columnas,int eliminadasTurno,int cascadasTurno,int combinacionesTurno,int totalFichasEliminadas,int totalCombinaciones,int turnosUsuario,int puntuacion);

int pedirAccion(int filas, int columnas);

void actualizarEstadisticas(int eliminadasTurno,int cascadasTurno,int combinacionesTurno,int& totalFichasEliminadas,int& totalCombinaciones,
int& turnosUsuario,
int& puntuacion,
bool esJugadaUsuario);

bool procesarModificacionTablero(int accion,unsigned char*& tablero,unsigned char*& marcas,int& filas,int& columnas,int& bytesReservados,
int& eliminadasTurno,
int& cascadasTurno,
int& combinacionesTurno);

void ejecutarJugadaUsuario(unsigned char* tablero,unsigned char* marcas,int filaSeleccionada,int filas, int columnas,int& eliminadasTurno,
int& cascadasTurno,
int& combinacionesTurno,
int& totalFichasEliminadas,
int& totalCombinaciones,
int& turnosUsuario,
int& puntuacion);


int inicializarJuego(unsigned char*& tablero,unsigned char*& marcas,int filas,int columnas);

bool pedirDimensiones(int& filas, int& columnas);

#endif // JUEGO_H