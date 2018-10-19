/* ===================================================================
File: conjunto_simbolos.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD conjunto_simbolos
=================================================================== */

#ifndef CONJUNTO_SIMBOLOS_H
#define CONJUNTO_SIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CADENA "cadena"

typedef struct _Conjunto_simbolos Conjunto_simbolos;

/** Funciones */

/**Creamos e inicializamos un conjunto nuevo*/
Conjunto_simbolos* conjunto_simbolos_create(char *nombre);

/** Insertar symbolo en el conjunto*/
void insert_simbolo(Conjunto_simbolos *conjunto_simbolos, char *sym);

/**Liberamos la memoria de un conjunto_simbolos*/
void conjunto_simbolos_destroy(Conjunto_simbolos *conjunto_simbolos);

char** get_simbolos(Conjunto_simbolos *conjunto_simbolos);

/**Obtener el nombre del conjunto_simbolos*/
char* get_nombre_conjunto(Conjunto_simbolos *conjunto_simbolos);

/** Ver si un símbolo esta contenido en el conjunto **/
int is_in_conjunto_simbolos(Conjunto_simbolos *conjunto_simbolos, char *sym);

/**Obtener el numero de simbolos del conjunto_simbolos*/
int get_num_simbolos(Conjunto_simbolos *conjunto_simbolos);

/** Función que nos facilitará la impresión de un conjunto_simbolos*/
void print_conjunto_simbolos(FILE *f, Conjunto_simbolos *conjunto_simbolos, int pos);


#endif