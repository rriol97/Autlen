/* ===================================================================
File: transicion.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Transicion. Se implementa como una tabla.
=================================================================== */

#include "transicion.h"


/** Estructura de estado*/
struct _Transicion {
	int ***transiciones;
	int dim_matriz;
	int num_tablas;
};

/** Funciones */

/**Creamos e inicializamos una transicion nueva*/
Transicion* transicion_create(int num_simb, int num_estados) {
	int i, k, j;
	Transicion *trans = NULL;

	if (num_estados == 0 || num_simb == 0) {
		return NULL;
	}

	trans = (Transicion*) malloc (sizeof(Transicion));

	if(!trans) {
		return NULL;
	}

	trans->transiciones = (int***) malloc(sizeof(int**) * num_simb);

	if (!trans->transiciones){
		free(trans);
		return NULL;
	}

	for(i = 0; i < num_simb; i++){
		trans->transiciones[i] = (int**) malloc(sizeof(int*) * num_estados);

		if (!trans->transiciones[i]) {
			for (k = 0; k < i; k++){
					free(trans->transiciones[k]);
			}
			return NULL;
		}

	}

	for (k = 0; k < num_simb; k++) {
		for (i = 0; i < num_estados; i++) {
			trans->transiciones[k][i] = (int*) malloc(sizeof(int) * num_estados);

			if (!trans->transiciones[k][i]) {

				for (k = 0; k < num_simb; k++) {
					for (j = 0; j < i; j++) {
						free(trans->transiciones[k][j]);
					}
			
				}

				return NULL;	
			}	
		}
	}
	
	/** Inicializamos el la estrcutura de transicion*/

	trans->dim_matriz = num_estados;
	trans->num_tablas = num_simb;

	for (k = 0; k < num_simb; k++) {
		for (i = 0; i < num_estados; i++) {
			for (j = 0; j < num_estados; j++) {
				trans->transiciones[k][i][j] = 0;
			}
		}
	}

	return trans;

}

/** Liberamos la memoria de una transicion*/
void transicion_destroy(Transicion *transicion) {
	int i,k;

	if (!transicion) {
		return;
	}

	for (k = 0; k < transicion->num_tablas; k++) {
		for (i = 0; i < transicion->dim_matriz; i++) {
			free(transicion->transiciones[k][i]);
		}
	}

	for(k = 0; k < transicion->num_tablas; k++) {
		free(transicion->transiciones[k]);
	}

	free(transicion->transiciones);
	free(transicion);

	return;
}

/**Obtenemos el valor de la transicion*/
int get_valor_transicion(Transicion *trans, int simbolo, int estado1, int estado2){

	if (simbolo < 0 || simbolo >= trans->num_tablas || estado1 < 0 || estado1 >=trans->dim_matriz || estado2 < 0 || estado2 >=trans->dim_matriz) {
		return -1;
	}

	return trans->transiciones[simbolo][estado1][estado2];

}

/**Obtenemos el valor de la transicion*/
void set_valor_transicion(Transicion *trans, int simbolo, int estado1, int estado2){

	if (simbolo < 0 || simbolo >= trans->num_tablas || estado1 < 0 || estado1 >=trans->dim_matriz || estado2 < 0 || estado2 >=trans->dim_matriz) {
		return;
	}

	trans->transiciones[simbolo][estado1][estado2] = 1;

	return;

}

/**Imprimir tabla de simbolos*/
void transicion_print(Transicion *transicion){
	int i,j,k;

	for (k = 0; k < transicion->num_tablas; k++) {
		printf("Tabla del simbolo %d\n", k);
		for (i = 0; i < transicion->dim_matriz; i++){
			for (j = 0; j < transicion->dim_matriz; j++){
				printf("%d", transicion->transiciones[k][i][j]);;
			}

			printf("\n");
		}
	}	

	return;
}


