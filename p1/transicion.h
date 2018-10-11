/* ===================================================================
File: transicion.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Transicion.
=================================================================== */

#ifndef TRANSICION_H
#define TRANSICION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"

typedef struct _Transicion Transicion;

/** Funciones */

/**Creamos e inicializamos una transicion nueva*/
Transicion* transicion_create(int num_simb, int num_estados);

/** Liberamos la memoria de una transicion*/
void transicion_destroy(Transicion *transicion);

/**Obtenemos el valor de la transicion*/
int get_valor_transicion(Transicion *transicion, int simbolo, int estado1, int estado2);

/**Obtenemos el valor de la transicion*/
void set_valor_transicion(Transicion *transicion, int simbolo, int estado1, int estado2);

/**Imprimir tabla de simbolos*/
void transicion_print(Transicion *transicion);

#endif