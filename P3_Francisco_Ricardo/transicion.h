/* ===================================================================
File: transicion.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Transicion.
=================================================================== */
#ifndef TRANSICION_H
#define TRANSICION_H

#include "estado.h"
#include "afnd.h"

#define NO_EXISTE 0
#define EXISTE 1
#define ERR -1
#define NO_INI -2
#define LAMBDA "l"
#define ANCHO 6

#define TAM 64 // tamano maximo para nombres de simbolos y estados

typedef struct _Transicion Transicion;

/** Funciones */

/**Creamos e inicializamos una transicion nueva*/
Transicion *transicion_create(int num_simb, int num_estados);

/** Liberamos la memoria de una transicion*/
void transicion_destroy(Transicion *transicion);

/**Obtenemos el valor de la transicion*/
int get_valor_transicion(Transicion *transicion, char *simbolo, char *estado1, char *estado2);

/**Obtenemos el valor de la transicion*/
void set_valor_transicion(Transicion *transicion, char *simbolo, char *estado1, char *estado2);

/**Imprimir tabla de simbolos*/
void transicion_print(AFND *afnd, FILE *f, Transicion *transicion);

/**Induce transiciones por transitividad*/
void transicion_inducir(Transicion *t);

/**Incluye los nombres de estados si no lo estaban y devuleve su posicion dentro 
 * del array en caso de que ya estuvieran*/
int mapear_estado(Transicion *t, char *est);

int mapear_simbolo(Transicion *t, char *sim);

#endif