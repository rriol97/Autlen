/* ===================================================================
File: alfabeto.h
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Alfabeto
=================================================================== */

#ifndef ALFABETO_H
#define ALFABETO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Alfabeto Alfabeto;

/** Funciones */

/**Creamos e inicializamos un alfabeto nuevo*/
Alfabeto* alfabeto_create();

/** Insertar symbolo en alfabeto*/
void insertar_simbolo (Alfabeto *alfabeto, char *sym);

/**Liberamos la memoria de un alfabeto*/
void alfabeto_destroy(Alfabeto *alfabeto);

/**Obtener el nombre del alfabeto*/
char** get_simbolos(Alfabeto *alfabeto);

/**Obtener el numero de simbolos del alfabeto*/
int get_num_simbolos(Alfabeto *alfabeto);

/** Función que nos facilitará la impresión de un alfabeto*/
void print_alfabeto(Alfabeto *alfabeto);


#endif