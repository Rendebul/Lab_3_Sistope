#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "funciones.h"
#include <pthread.h>

float ** crearMatriz(int i){
    float ** matriz = (float**)malloc(sizeof(float*)*i);
    if(!matriz) {
        printf("Error al asignar memoria\n");
        exit(-1);
    }

    for (int aux = 0; aux < i; ++aux)
    {
        matriz[aux] = (int*)malloc(sizeof(int)*i);
        if(!matriz[aux]) {
            printf("Error al asignar memoria\n");
            exit(-1);
        }
    }
    return matriz;
};

float ** inicializarMatriz(int i, float **matriz) {
    for (int aux = 0; aux < i; ++aux)
    {
        for (int aux2 = 0; aux2 < i; ++aux2)
        {   
            matriz[aux][aux2] = 0;
        }
    }

    return matriz;
};

void liberarMatriz(int i, float ** matriz) {
    for (int linea = 0; linea < i; ++linea)
    {
        free(matriz[linea]);
    }
};

void imprimirMatriz(int i, float ** matriz) {
    for (int linea = 0; linea < i; ++linea)
    {
        for (int columna = 0; columna < i; ++columna)
        {
           printf("%i", matriz[linea][columna]);
        }
        printf("\n");
    }
};

float ** moverMatriz(float ** matriz, float ** matriz_t1, int** matriz_t2, int tam) {
    for (int i = 1; i < tam-1; ++i)
    {
        for (int j = 1; j < tam-1; ++j)
        {
            matriz[i][j] = 2*matriz_t1[i][j] - matriz_t2[i][j] + (1.0*1.0)*(0.1/0.2)(4 * matriz_t1[i][j] + matriz_t1[i+1][j] + matriz_t1[i-1][j] + matriz_t1[i][j+1] + matriz_t1[i][j-1])
        }
    }

    return int ** matriz;
};