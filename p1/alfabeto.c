/* ===================================================================
File: alfabeto.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Alfabeto
=================================================================== */

#include "alfabeto.h"

/** Estructura de alfabeto*/
struct _Alfabeto {
    char **simbolos;
    int nsym;
};


/** Funciones a implementar */

/**Creamos e inicializamos un alfabeto vacio nuevo*/
Alfabeto* alfabeto_create() {
	Alfabeto *alfabeto = NULL;

	alfabeto = (Alfabeto*) malloc (sizeof(Alfabeto));

	if (!alfabeto) {
		return NULL;
	}

	alfabeto->simbolos = NULL;
	alfabeto->nsym = 0;

	return alfabeto;
}

/** Insertamos u síbolo nuevo en el alfabeto*/
void insertar_simbolo (Alfabeto *alfabeto, char *sym) {
	if (!alfabeto || !sym) {
		return;
	}
	
	/** Si es el primer simbolo */
	if (alfabeto->nsym == 0) {

		alfabeto->simbolos = (char**) malloc (sizeof (char*));

		if (!alfabeto->simbolos) {
			return;
		}
	} 

	/**Si ya hay simbolos en el alfabeto */
	else {

		alfabeto->simbolos = (char**) realloc (alfabeto->simbolos, sizeof (char*) * 2 * (alfabeto->nsym +1) ); 

		if (!alfabeto->simbolos) {
			return;
		}		
	}

	alfabeto->simbolos[alfabeto->nsym] = (char*) malloc (sizeof(char) * strlen(sym) + 1);

	if (!alfabeto->simbolos[alfabeto->nsym]) {
			return;
	}	

	strcpy(alfabeto->simbolos[alfabeto->nsym], sym);
	alfabeto->nsym ++;

	return;
}

/**Liberamos la memoria de un alfabeto*/
void alfabeto_destroy(Alfabeto *alfabeto){
	int i;

	if (!alfabeto){
		return;
	}

	if (alfabeto->nsym == 0){
		free (alfabeto);
		return;
	}

	for (i = 0; i < alfabeto->nsym; i++) {
		free(alfabeto->simbolos[i]);
	}

	free(alfabeto->simbolos);

	free(alfabeto);
}

/**Obtener el nombre del alfabeto*/
char** get_simbolos(Alfabeto *alfabeto){

	if (!alfabeto){
		return NULL;
	}

	return alfabeto->simbolos;
}

/**Obtener el numero de simbolos del alfabeto*/
int get_num_simbolos(Alfabeto *alfabeto){

	if (!alfabeto){
		return -1;
	}

	return alfabeto->nsym;
}

/** Función que nos facilitará la impresión de un alfabeto*/
void print_alfabeto(Alfabeto *alfabeto){
	int simbolo;

	if (alfabeto->nsym == 0){
		printf("No hay simbolos en el alfabeto\n");
		return;
	}

	for (simbolo = 0; simbolo < alfabeto->nsym; simbolo++){
		printf("%s\n", alfabeto->simbolos[simbolo]);
	}

	return;
}

