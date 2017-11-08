#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

float ** crearMatriz(int i);
float ** inicializarMatriz(int i, float ** matriz);
float ** inicializarMatrizInicial(int i, float ** matriz);
int contar(char *nombre);
int* asignar(int num, int num_hilos);
void liberarMatriz(int i, float ** matriz);
void imprimirMatriz(int i, float ** matriz);
float ** moverMatriz(float ** matriz, float ** matriz_t1, float ** matriz_t2, int tam);
float ** moverMatrizInicial(float ** matriz, float ** matriz_t1, int tam);
float ** copiarMatriz(float ** matriz, float ** matriz_2, int tam);