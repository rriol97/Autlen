/* ===================================================================
File: estado.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Estado
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

/**Creamos e inicializamos un estado nuevo*/
Estado* estado_create(char *nombre, TIPO tipo);

/**Liberamos la memoria de un estado*/
void estado_destroy(Estado *estado);

/**Obtener el nombre del estado*/
char* get_name_estado(Estado *estado);

/** Obtenemos el tipo de estado (Inicial, final o normal)*/	
TIPO get_tipo_estado(Estado *estado);

/** Función que nos facilitará la impresión de un estado*/
void print_estado(Estado *estado);

#endif