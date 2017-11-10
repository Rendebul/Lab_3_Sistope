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
    int aux;
    for (aux = 0; aux < i; ++aux)
    {
        matriz[aux] = (float*)malloc(sizeof(float)*i);
        if(!matriz[aux]) {
            printf("Error al asignar memoria\n");
            exit(-1);
        }
    }
    return matriz;
};

float ** inicializarMatrizInicial(int i, float **matriz) {
    int aux, aux2;
    for (aux = 0; aux < i; ++aux)
    {
        for (aux2 = 0; aux2 < i; ++aux2)
        {   
            if (aux > (0.4*i-1) && aux < (0.6*i-1) && aux2 > (0.4*i-1) && aux2 < (0.6*i-1)) {
                matriz[aux][aux2] = 20;
            } else {
                matriz[aux][aux2] = 0;
            }
        }
    }
    return matriz;
};

float ** inicializarMatriz(int i, float **matriz) {
    int aux, aux2;
    for (aux = 0; aux < i; ++aux)
    {
        for (aux2 = 0; aux2 < i; ++aux2)
        {   
            matriz[aux][aux2] = 0;

        }
    }
    return matriz;
};

void liberarMatriz(int i, float ** matriz) {
    int linea;
    for (linea = 0; linea < i; ++linea)
    {
        free(matriz[linea]);
    }
};

void imprimirMatriz(int i, float ** matriz) {
    int linea, columna;
    for (linea = 0; linea < i; ++linea)
    {
        for (columna = 0; columna < i; ++columna)
        {
           printf("|%f|", matriz[linea][columna]);
        }
        printf("\n");
    }
};

float ** moverMatriz(float ** matriz, float ** matriz_t1, float ** matriz_t2, int tam, int desde, int hasta) {
    int i, j;
    for (i = desde; i < hasta; ++i)
    {
        for (j = 1; j < tam-1; ++j)
        {
            matriz[i][j] = (2*matriz_t1[i][j]) - (matriz_t2[i][j]) + (((1.0)*((0.1/0.2)*(0.1/0.2)))*(matriz_t1[i+1][j] + matriz_t1[i-1][j] + matriz_t1[i][j+1] + matriz_t1[i][j-1] - 4 * matriz_t1[i][j]));
        }
    }

    return matriz;
};

float ** moverMatrizInicial(float ** matriz, float ** matriz_t1, int tam, int desde, int hasta) {
    int i, j;
    for (i = desde; i < hasta; ++i)
    {
        for (j = 1; j < tam-1; ++j)
        {
            matriz[i][j] = matriz_t1[i][j] + (1.0)*(((0.1/0.2)*(0.1/0.2))/2)*(matriz_t1[i+1][j] + matriz_t1[i-1][j] + matriz_t1[i][j+1] + matriz_t1[i][j-1] - (4.0) * matriz_t1[i][j]);
        }
    }

    return matriz;
};

float ** copiarMatriz(float ** matriz, float ** matriz_2, int tam) {
    int i, j;
    for (i = 0; i < tam; ++i)
    {
        for (j = 0; j < tam; ++j)
        {
            matriz_2[i][j] = matriz[i][j];
        }
    }

    return matriz;
};

int* asignar(int num, int num_hebras) {
    int piso = floor((double)num/num_hebras);
    int *asignacion = malloc(sizeof(int)*num_hebras);
    int diferencia = (num%num_hebras);
    int i;
    for (i = 0; i < num_hebras; ++i)
    {
        asignacion[i] = piso;
    }

    for (i = 0; i < diferencia; ++i)
    {
        asignacion[i] += 1;
    }

    return asignacion;
};

data* asignarData(int* asignacion, int tam_matriz, int num_hebras) {
    data* arregloDatos = (data*)malloc(sizeof(data)*num_hebras);
    int palabra_ant = 1;
    int i;
    for (i = 0; i < num_hebras; ++i)
    {   
        int fila_inicio = palabra_ant;
        int fila_termino = palabra_ant + asignacion[i];
        data dato = {i, fila_inicio, fila_termino, tam_matriz};
        arregloDatos[i] = dato;
        palabra_ant += asignacion[i];
    }
    return arregloDatos;
}

void imprimirData(data* datos, int num_hebras){
    int i;
    for (i = 0; i < num_hebras; ++i)
    {
        printf("Impresión datos:\n");
        printf("id: %d\n", datos[i].id);
        printf("fila inicio: %d\n", datos[i].fila_inicio);
        printf("fila termino: %d\n", datos[i].fila_termino);
        printf("tam matrix: %d\n", datos[i].tam_matriz);
    }
}

void salidaArchivo(float ** matriz, char * salida, int tam){
    FILE *fa;
    fa = fopen(salida, "wb");
    if(fa==NULL) {
        printf("Error al abrir el archivo\n");
        abort();
    }
    int i;
    for (i = 0; i < tam; ++i)
    {
        fwrite(matriz[i], tam, sizeof(float), fa);
    }

    fclose(fa);
};