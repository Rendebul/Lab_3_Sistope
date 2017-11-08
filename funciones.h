#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

float ** crearMatriz(int i);
float ** inicializarMatriz(int i, int** matriz);
int contar(char *nombre);
int* asignar(int num, int num_hilos);
void liberarMatriz(int i, float ** matriz);
void imprimirMatriz(int i, float ** matriz);
float ** moverMatriz(float ** matriz, float ** matriz_t1, float ** matriz_t2);