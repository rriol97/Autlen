/* ===================================================================
File: estado.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Estado
=================================================================== */
#include "estado.h"

/** Estructura de estado*/
struct _Estado {
	int id;
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
		return "Normal";
	}

	else {
		return "Inicial y final";
	}
}

/** Funciones a implementar */
Estado* estado_create(char *nombre, TIPO tipo, int id) {
	Estado *estado = NULL;

	if (!nombre) {
		return NULL;
	}

	estado = (Estado*) malloc(sizeof(Estado)); /**Reservamos memoria para un estado*/
	if (!estado){
		return NULL;
	}

	// +2 para fin de cadena y posible asterisco
	estado->nombre = (char*) malloc(sizeof(char) * strlen(nombre) + 2);
	if (!estado->nombre){
		free(estado);
		return NULL;
	}

	strcpy(estado->nombre, nombre);
	if (tipo == FINAL) {
		strcat(estado->nombre, "*");
	}
	estado->tipo = tipo;
	estado->id = id;

	return estado;
}

void estado_destroy(Estado *estado) {

	if (!estado) {
		return;
	}

	free(estado->nombre);
	free(estado);
	return;
}

char* get_name_estado(Estado* estado) {

	if (!estado){
		return NULL;
	}

	return estado->nombre;
}

TIPO get_tipo_estado(Estado *estado) {

	if (!estado){
		return -1;
	}

	return estado->tipo;	
}

void print_estado(FILE* f, Estado* estado) {

	if (!f) {
		return;
	}
	if (!estado) {
		fprintf(f, "-");
		return;
	}

	fprintf(f, "%s (%s)", estado->nombre, texto_enum(estado->tipo));
	return;
}	

TIPO estado_get_id(Estado *estado) {

	if (!estado) {
		return ERROR;
	}

	return estado->id;	
}

/*Funcion que compara dos estados: devuelve 1 si son iguales y 0 en caso contrario**/
int estado_equal(Estado *estado1, Estado *estado2){

	if (!estado1 || !estado2){
		return -1;
	}

	if (estado1->id == estado2->id){
		return 1;
	}

	return 0;
}