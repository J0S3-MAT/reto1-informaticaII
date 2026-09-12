#include "bits.h"

int calcularCantidadBytes(int filas, int columnas) {
    int cantidad_bits = filas * columnas * 3;
    int cantidad_bytes = cantidad_bits / 8;
    if (cantidad_bits % 8 != 0) {
        cantidad_bytes += 1;
    }
    return cantidad_bytes;
}

int calcularIndice(int fila, int columna, int columnas) {
    return fila * columnas + columna;
}

unsigned char leerFicha(const unsigned char* tablero, int fila, int columna, int columnas) {
    int indice = calcularIndice(fila, columna, columnas);
    int bit_inicial = indice * 3;
    int byte_inicial = bit_inicial / 8;
    int desplazamiento = bit_inicial % 8;

    if (desplazamiento <= 5) {
        // Caso 1: Los 3 bits están en el mismo byte
        // Desplazamos a la derecha y aplicamos la máscara 0b111 (7 en decimal)
        unsigned char valor = (tablero[byte_inicial] >> desplazamiento) & 0x07;
        return valor;
    } else {
        // Caso 2: La ficha está repartida entre dos bytes
        int bits_primer_byte = 8 - desplazamiento; // Cuántos bits hay en el primer byte (1 o 2)
        int bits_segundo_byte = 3 - bits_primer_byte; // Los bits restantes en el siguiente byte

        // Extraer los bits del primer byte
        unsigned char parte1 = (tablero[byte_inicial] >> desplazamiento);

        // Extraer los bits del segundo byte y enmascararlos
        unsigned char mascara_segundo = (1 << bits_segundo_byte) - 1;
        unsigned char parte2 = tablero[byte_inicial + 1] & mascara_segundo;

        // Combinar ambas partes
        unsigned char valor = parte1 | (parte2 << bits_primer_byte);
        return valor & 0x07;
    }
}

void escribirFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valor) {
    valor &= 0x07; // Nos aseguramos de tomar solo los 3 bits menos significativos

    int indice = calcularIndice(fila, columna, columnas);
    int bit_inicial = indice * 3;
    int byte_inicial = bit_inicial / 8;
    int desplazamiento = bit_inicial % 8;

    if (desplazamiento <= 5) {
        // Caso 1: Toda la ficha cae en un solo byte
        // 1. Limpiar los 3 bits en esa posición con una máscara invertida
        tablero[byte_inicial] &= ~(0x07 << desplazamiento);
        // 2. Insertar el nuevo valor en la posición correspondiente
        tablero[byte_inicial] |= (valor << desplazamiento);
    } else {
        // Caso 2: La ficha está repartida entre dos bytes
        int bits_primer_byte = 8 - desplazamiento;

        // --- Primer Byte ---
        // Limpiar los bits correspondientes al final del primer byte
        unsigned char mascara_limpieza1 = (1 << bits_primer_byte) - 1;
        tablero[byte_inicial] &= ~(mascara_limpieza1 << desplazamiento);

        // Escribir la primera parte del valor
        tablero[byte_inicial] |= ((valor & mascara_limpieza1) << desplazamiento);

        // --- Segundo Byte ---
        int bits_segundo_byte = 3 - bits_primer_byte;
        unsigned char mascara_limpieza2 = (1 << bits_segundo_byte) - 1;

        // Limpiar los primeros bits del segundo byte
        tablero[byte_inicial + 1] &= ~mascara_limpieza2;

        // Escribir la segunda parte del valor
        tablero[byte_inicial + 1] |= (valor >> bits_primer_byte) & mascara_limpieza2;
    }
}