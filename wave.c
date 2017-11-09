#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "funciones.h"
#include <pthread.h>

float **matriz;
float **matriz_t1;
float **matriz_t2;
int i;

void *run(void *params) {
    //printf("Hola!\n");
    data* datos = (data *)params;
    int id = (int)datos->id;
    int fila_inicio = (int)datos->fila_inicio;
    int fila_termino = (int) datos->fila_termino;
    int tam_tam = (int) datos->tam_matriz;
    
    //printf("Soy: %d, fila: %d, fila_term: %d, tam: %d \n", id, fila_inicio, fila_termino, tam_tam);

    if (i > 1)
    {
      matriz = moverMatriz(matriz, matriz_t1, matriz_t2, tam_tam, fila_inicio, fila_termino);
    } else if (i == 1){

      matriz = moverMatrizInicial(matriz, matriz_t1, tam_tam, fila_inicio, fila_termino);
    }
}

int main(int argc, char **argv)
{
  //Se declaran variables
  int tam_matriz, iteraciones, numero_hebras = 0;
  int c;
  bool mostrar = false;
  pthread_t* hilos;

  opterr = 0;

    //Se capta el getopt correspondiente al coordinador.
  while ((c = getopt (argc, argv, "i:h:n:d::")) != -1)
    switch (c) {
        case 'n':
                    tam_matriz = atoi(optarg);
                    break;
        case 'i':
                    iteraciones = atoi(optarg);
                    break;
        case 'h':
                    numero_hebras = atoi(optarg);
                    break;
        case 'd':   
                    mostrar = true;
                    break;
        case '?':
                    if (optopt == 'm' || optopt == 'n' || optopt == 'i' || optopt == 'h')
                        fprintf (stderr, "La opcion -%c requires un argumento.\n", optopt);
                    else if (isprint (optopt))
                        fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
                    else
                        fprintf (stderr,"Caracter desconocido `\\x%x'.\n",optopt);
                    return 1;
        default:
                abort ();
  }
  printf (" n = %d, m = %d, h = %d, d = %d\n", tam_matriz, iteraciones, numero_hebras, mostrar);
  if(tam_matriz < 1){
    printf("Tamaño incorrecto para inicializar tablero\n");
    abort();
  }
  if(iteraciones < 1){
    printf("Tamaño incorrecto para inicializar tablero\n");
    abort();
  }
  if(numero_hebras < 1){
    printf("Tamaño incorrecto para inicializar hebras\n");
    abort();
  }
  
  matriz = crearMatriz(tam_matriz);
  matriz = inicializarMatrizInicial(tam_matriz, matriz);
  
  matriz_t1 = crearMatriz(tam_matriz);
  matriz_t1 = inicializarMatriz(tam_matriz, matriz_t1);
  
  matriz_t2 = crearMatriz(tam_matriz);
  matriz_t2 = inicializarMatriz(tam_matriz, matriz_t2);
  int *asignacion = asignar(tam_matriz-2, numero_hebras);
  data *datos = asignarData( asignacion, tam_matriz, numero_hebras);
  imprimirData(datos, numero_hebras);

  imprimirMatriz(tam_matriz, matriz);

  hilos = (pthread_t *)malloc(sizeof(pthread_t)*numero_hebras);


  for (i = 0; i <= iteraciones;)
  {
    if (mostrar)
    {
      printf("Iteracion numero: %d\n", i);
    }
    int aux;
    for (aux = 0; aux < numero_hebras; ++aux)
    {
      pthread_create(&hilos[aux], NULL, run, (void *)&datos[aux]);
    }

    for (aux = 0; aux < numero_hebras; ++aux)
    {
      pthread_join(hilos[aux], NULL);
    }

    matriz_t2 = copiarMatriz(matriz_t1, matriz_t2, tam_matriz);
    matriz_t1 = copiarMatriz(matriz, matriz_t1, tam_matriz);

    if (mostrar)
    {
      imprimirMatriz(tam_matriz, matriz_t1);
    }
    i += 1;
  }
  liberarMatriz(tam_matriz, matriz_t1);
  liberarMatriz(tam_matriz, matriz_t2);
  liberarMatriz(tam_matriz, matriz);
  return 0;
}