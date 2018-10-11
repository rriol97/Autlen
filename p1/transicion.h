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
Transicion* transicion_create(Estado *estado_inicial, Estado *estado_final, char *valor);

/**Liberamos la memoria de una transicion*/
void transicion_destroy(Transicion *transicion);

/** Obtenemos el estado final de la transicion*/
Estado* transicion_get_estado_inicial(Transicion *transicion);

/** Obtenemos el estado final de la transicion*/
Estado* transicion_get_estado_final(Transicion *transicion);

/**Obtenemos el valor del alfabeto que determina la transicion*/
char* transicion_get_valor(Transicion *transicion);

/**Imprimir una transicion*/
void transicion_print(Transicion *transicion);

#endif