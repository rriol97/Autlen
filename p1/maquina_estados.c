/* ===================================================================
File: maquina_estados.c
Authors: Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include <stdio.h>
#include "afnd.h"
#include "estado.h"
#include "conjunto_simbolos.h"
#include "transicion.h"



int main(int argc, char **argv) {

/* DECLARACIÓN DE UN PUNTERO A UN AFND */
	AFND *p_afnd = NULL;

/* INICIALIZACIÓN DE UN NUEVO AFND DE NOMBRE af1 Y CON 3 ESTADOS Y 2 SÍMBOLOS EN SU ALFABETO */	
	p_afnd = AFNDNuevo("af1",3,2);

/* DEFINICIÓN DEL ALFABETO DEL AFND */
	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
	AFNDInsertaEstado(p_afnd,"q0",INICIAL);
	AFNDInsertaEstado(p_afnd,"q1",NORMAL);
	AFNDInsertaEstado(p_afnd,"qf",FINAL);	

/* DEFINICIÓN DE LAS TRANSICIONES NO LAMBDA */
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");

	AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");

	AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");

	AFNDInsertaTransicion(p_afnd, "q0", "1", "qf");

/* SE MUESTRA EL AFND DEFINIDO */
	fprintf(stdout,"\n****************** AFND *********************\n");
	AFNDImprime(stdout,p_afnd);
	fprintf(stdout,"\n*********************************************\n");	

/* DEFINICIÓN DE LA CADENA DE ENTRADA [ 0 1 0 1 1 ] */
	p_afnd= AFNDInsertaLetra(p_afnd,"0");
	p_afnd= AFNDInsertaLetra(p_afnd,"1");
	p_afnd= AFNDInsertaLetra(p_afnd,"0");
	p_afnd= AFNDInsertaLetra(p_afnd,"1");
	p_afnd= AFNDInsertaLetra(p_afnd,"1");


	AFNDElimina(p_afnd);	

	return 0;

}