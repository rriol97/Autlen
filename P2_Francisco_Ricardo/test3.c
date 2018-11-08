/* ===================================================================
File: test3.c
Authors: Ricardo Riol gonzalez, Francisco de Vicente Lana

Main de pruebas numero 3, un ejemplo donde se inducen lambdas por 
reflexividad. Sacado de clase de teoria
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
	p_afnd = AFNDNuevo("afl1", 4, 2);

	/* DEFINICIÓN DEL ALFABETO DEL AFND */
	AFNDInsertaSimbolo(p_afnd, "a");
	AFNDInsertaSimbolo(p_afnd, "b");

	/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
    AFNDInsertaEstado(p_afnd,"q0",INICIAL);
    AFNDInsertaEstado(p_afnd,"q1",NORMAL);
    AFNDInsertaEstado(p_afnd,"q2",NORMAL);
    AFNDInsertaEstado(p_afnd,"q3",FINAL);

	/* DEFINICIÓN DE LAS TRANSICIONES NO LAMBDA */
    AFNDInsertaTransicion(p_afnd, "q0", "b", "q2");
    AFNDInsertaTransicion(p_afnd, "q1", "b", "q3");
    AFNDInsertaTransicion(p_afnd, "q2", "a", "q1");
    AFNDInsertaTransicion(p_afnd, "q3", "a", "q2");

    /** DEFINICIÓN DE LAS TRANSICIONES LAMBDA*/
    AFNDInsertaLTransicion(p_afnd, "q2", "q3");
    AFNDInsertaLTransicion(p_afnd, "q3", "q2");

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

	/**INTRODUCIMOS NUEVA CADENA DE ENTRADA [ baababaa ], aceptada */
	p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");

	p_afnd = AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

	/**NUEVA CADENA DE ENTRADA [ baaa ], aceptada */
	p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);


/*********************************************************************************/

    /**NUEVA CADENA DE ENTRADA [ baaab ], aceptada */
    p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"b");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"b");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

    /**NUEVA CADENA DE ENTRADA [ aaaaa ], no aceptada */
    p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
    AFNDInsertaLetra(p_afnd,"a");
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