/* ===================================================================
File: estado.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Estado
=================================================================== */
#include "estado.h"

/** Estructura de estado*/
struct _Estado {
    char *nombre;
    TIPO tipo;
};

/** Funciones privadas */
char* texto_enum(TIPO t) {
	if (t == INICIAL){
		return "Inicial";
	}

	else if (t == FINAL) {
		return "Final";
	}

	else if (t == NORMAL) {
		return "NORMAL";
	}

	else {
		return "INICIAL_Y_FINAL";
	}
}

/** Funciones a implementar */
Estado* estado_create(char *nombre, TIPO tipo) {
	Estado *estado = NULL;

	if (!nombre) {
		return NULL;
	}

	estado = (Estado*) malloc(sizeof(Estado)); /**Reservamos memoria para un estado*/
	if (!estado){
		return NULL;
	}

	estado->nombre = (char*) malloc(sizeof(char) * strlen(nombre) + 1);
	if (!estado->nombre){
		free(estado);
		return NULL;
	}

	strcpy(estado->nombre, nombre);
	estado->tipo = tipo;

	return estado;
}

void estado_destroy(Estado *estado){

	if (!estado){
		return;
	}

	free(estado->nombre);
	free(estado);
	return;
}

char* get_name_estado(Estado* estado){

	if (!estado){
		return NULL;
	}

	return estado->nombre;
}

TIPO get_tipo_estado(Estado *estado){

	if (!estado){
		return -1;
	}

	return estado->tipo;	
}

void print_estado(Estado *estado){

	if (!estado){
		return;
	}

	printf("Nombre: %s\nTipo: %s\n", estado->nombre, texto_enum(estado->tipo));
	return;
}	
