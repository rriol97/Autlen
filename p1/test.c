/* ===================================================================
File: maquina_estados.c
Authors: Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include <stdio.h>
#include "afnd.h"

// valgrind --leak-check=full ./test

int main(int argc, char **argv) {

/* DECLARACIÓN DE UN PUNTERO A UN AFND */
	AFND *p_afnd = NULL;

/* INICIALIZACIÓN DE UN NUEVO AFND DE NOMBRE af1 Y CON 3 ESTADOS Y 2 SÍMBOLOS EN SU ALFABETO */	
	p_afnd = AFNDNuevo("af1", 3, 2);

/* SE MUESTRA EL AFND DEFINIDO */
	fprintf(stdout,"\n****************** AFND *********************\n");
	AFNDImprime(stdout, p_afnd);
	fprintf(stdout,"\n*********************************************\n");	

	AFNDElimina(p_afnd);	

	return 0;

}