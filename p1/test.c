/* ===================================================================
File: maquina_estados.c
Authors: Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include <stdio.h>
#include "afnd.h"

// valgrind --leak-check=full ./test

int main(int argc, char **argv) {
	int test1 = FALSE;

/* DECLARACIÓN DE UN PUNTERO A UN AFND */
	AFND *p_afnd = NULL;

/* INICIALIZACIÓN DE UN NUEVO AFND DE NOMBRE af1 Y CON 3 ESTADOS Y 2 SÍMBOLOS EN SU ALFABETO */	
	p_afnd = AFNDNuevo("af1", 3, 2);

/* SE MUESTRA EL AFND DEFINIDO */
	//fprintf(stdout,"\n****************** AFND *********************\n");
	//AFNDImprime(stdout, p_afnd);
	//fprintf(stdout,"\n*********************************************\n");

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");	

	//fprintf(stdout,"\n****************** AFND *********************\n");
	//AFNDImprime(stdout, p_afnd);
	//fprintf(stdout,"\n*********************************************\n");

	AFNDInsertaEstado(p_afnd,"q0",INICIAL);
	AFNDInsertaEstado(p_afnd,"q1",NORMAL);
	AFNDInsertaEstado(p_afnd,"qf",FINAL);	

	//fprintf(stdout,"\n****************** AFND *********************\n");
	//AFNDImprime(stdout, p_afnd);
	//fprintf(stdout,"\n*********************************************\n");

	AFNDInicializaEstado(p_afnd);

	//fprintf(stdout,"\n****************** AFND *********************\n");
	//AFNDImprime(stdout, p_afnd);
	//fprintf(stdout,"\n*********************************************\n");

	p_afnd= AFNDInsertaLetra(p_afnd,"0");
	p_afnd= AFNDInsertaLetra(p_afnd,"1");
	p_afnd= AFNDInsertaLetra(p_afnd,"1");
	p_afnd= AFNDInsertaLetra(p_afnd,"0");
	p_afnd= AFNDInsertaLetra(p_afnd,"0");

	//fprintf(stdout,"\n****************** AFND *********************\n");
	//AFNDImprime(stdout, p_afnd);
	//fprintf(stdout,"\n*********************************************\n");

	AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "qf");
	
	fprintf(stdout,"\n****************** AFND *********************\n");
	AFNDImprime(stdout, p_afnd);
	fprintf(stdout,"\n*********************************************\n");

	test1 = AFNDProcesaEntrada(stdout, p_afnd);

	if (test1 == TRUE){
		fprintf(stdout, "CADENA RECONOCIDA\n");
	} 

	else {

		fprintf(stdout, "CADENA NO RECONOCIDA\n");
	}


	AFNDElimina(p_afnd);	

	return 0;

}