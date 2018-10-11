/* ===================================================================
File: estado.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Estado
=================================================================== */

#ifndef ESTADO_H
#define ESTADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Estado Estado;

typedef enum {
    INICIAL, NORMAL, INICIAL_y_FINAL, FINAL
} TIPO;

/** Funciones */

/**Creamos e inicializamos un estado nuevo*/
Estado* estado_create(char *nombre, TIPO tipo, int id);

/**Liberamos la memoria de un estado*/
void estado_destroy(Estado *estado);

/**Obtener el nombre del estado*/
char* get_name_estado(Estado *estado);

/** Obtenemos el tipo de estado (Inicial, final o normal)*/	
TIPO get_tipo_estado(Estado *estado);

/** Obtenemos el  identificador de estado*/	
TIPO get_id_estado(Estado *estado);

/** Función que nos facilitará la impresión de un estado*/
void print_estado(Estado *estado);

/*Funcion que compara dos estados: devuelve 1 si son iguales y 0 en caso contrario**/
int estado_equal(Estado *estado1, Estado *estado2);

#endif