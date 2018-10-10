/* ===================================================================
File: transicion.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Transicion.
=================================================================== */

#include "transicion.h"


/** Estructura de estado*/
struct _Transicion {
	Estado *estado;
	char *valor;
};

/** Funciones */

/**Creamos e inicializamos una transicion nueva*/
Transicion* transicion_create(Estado *estado, char *valor){
	Transicion *transicion = NULL;

	if(!estado) {
		return NULL;
	}

	transicion = (Transicion*) malloc(sizeof(Transicion));

	if(!transicion) {
		return NULL;
	}

	transicion->valor = (char*) malloc(sizeof(char) * strlen(valor) + 1);

	if (!transicion->valor){
		free(transicion);
		return NULL;
	}

	transicion->estado = estado;
	strcpy(transicion->valor, valor);

	return transicion;
}

/**Liberamos la memoria de una transicion*/
void transicion_destroy(Transicion *transicion){

	if(!transicion) {
		return;
	}

	free(transicion->valor);
	free(transicion);
	return;
}

/** Obtenemos el estado final de la transicion*/
Estado* transicion_get_estado(Transicion *transicion) {

	if(!transicion) {
		return NULL;
	}

	return transicion->estado;

}

/**Obtenemos el valor del alfabeto que determina la transicion*/
char* transicion_get_valor(Transicion *transicion) {

	if(!transicion) {
		return NULL;
	}

	return transicion->valor;
}

/**Imprimir una transicion*/
void transicion_print(Transicion *transicion) {

	if(!transicion) {
		return ;
	}

	print_estado(transicion_get_estado(transicion));
	printf("%s\n", transicion_get_valor(transicion));

	return;
}


