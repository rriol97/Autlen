/* ===================================================================
File: estado.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD estado.h
=================================================================== */

#ifndef ESTADO_H
#define ESTADO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Estado Estado;
typedef enum {
    INICIAL, fINAL, NORMAL
} TIPO;

/** Funciones */
Estado* estado_create(char *nombre, TIPO tipo);
void estado_destroy(Estado* estado);
char* get_name_estado(Estado* estado);
TIPO get_tipo_estado(Estado* estado);




#endif