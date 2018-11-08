/* ===================================================================
File: test5.c
Authors: Ricardo Riol gonzalez, Francisco de Vicente Lana

Main de pruebas numero 5, analiza el caso en el que haya mas de dos 
transiciones labmdas contiguas. 
=================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

int main(int argc, char **argv)
{
	/* DECLARACIÓN DE UN PUNTERO A UN AFND */
	AFND *p_afnd;

	/* INICIALIZACIÓN DE UN NUEVO AFND DE NOMBRE afl1 Y CON 8 ESTADOS Y 
    2 SÍMBOLOS EN SU ALFABETO */
	p_afnd = AFNDNuevo("afl1", 6, 3);

	/* DEFINICIÓN DEL ALFABETO DEL AFND */
	AFNDInsertaSimbolo(p_afnd, "a");
	AFNDInsertaSimbolo(p_afnd, "b");
    AFNDInsertaSimbolo(p_afnd, "c");

	/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
    AFNDInsertaEstado(p_afnd,"q0",INICIAL);
    AFNDInsertaEstado(p_afnd,"q1",NORMAL);
    AFNDInsertaEstado(p_afnd,"q2",NORMAL);
    AFNDInsertaEstado(p_afnd,"q3",NORMAL);
    AFNDInsertaEstado(p_afnd,"q4",NORMAL);
    AFNDInsertaEstado(p_afnd,"qf",FINAL);

	/* DEFINICIÓN DE LAS TRANSICIONES NO LAMBDA */
    AFNDInsertaTransicion(p_afnd, "q0", "a", "q1");
    AFNDInsertaTransicion(p_afnd, "q1", "a", "q1");
    AFNDInsertaTransicion(p_afnd, "q1", "b", "q4");
    AFNDInsertaTransicion(p_afnd, "q4", "c", "qf");
    AFNDInsertaTransicion(p_afnd, "q2", "b", "qf");
    AFNDInsertaTransicion(p_afnd, "q3", "c", "q3");

    /** DEFINICIÓN DE LAS TRANSICIONES LAMBDA*/
    AFNDInsertaLTransicion(p_afnd, "q1", "q2");
    AFNDInsertaLTransicion(p_afnd, "q2", "q3");
    AFNDInsertaLTransicion(p_afnd, "q3", "qf");

    AFNDImprime(stdout, p_afnd);

    /** INDUCIMOS EL RESTO DE TRANSICIONES LAMBDA*/
    AFNDCierraLTransicion(p_afnd);

    /* SE MUESTRA EL AFND DEFINIDO */
	AFNDImprime(stdout, p_afnd);

	/* DEFINICIÓN DE LA CADENA DE ENTRADA [] (cadena vacia), no aceptada */

	/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */
	p_afnd = AFNDInicializaEstado(p_afnd);

	/* SE MUESTRA LA CADENA ACTUAL */
	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

	/**INTRODUCIMOS NUEVA CADENA DE ENTRADA [ a ], aceptada */
	p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"a");

	p_afnd = AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

	/**NUEVA CADENA DE ENTRADA [ abc ], aceptada */
	p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"c");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);


/*********************************************************************************/

    /**NUEVA CADENA DE ENTRADA [ ba ], no aceptada */
    p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

    /**NUEVA CADENA DE ENTRADA [ aaabb ], no aceptada */
    p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"b");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

    /**NUEVA CADENA DE ENTRADA [ aba ], no aceptada */
    p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

	/* SE LIBERAN TODOS LOS RECURSOS ASOCIADOS CON EL AFND */
	AFNDElimina(p_afnd);

	return EXIT_SUCCESS;
}