/* ===================================================================
File: transicion.h
Authors: Ricardo Riol gonzalez, Francisco de Vicente Lana

Main de pruebas numero 1. Se trata del proporcionado en el enunciado
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
	p_afnd = AFNDNuevo("afl1", 8, 2);

	/* DEFINICIÓN DEL ALFABETO DEL AFND */
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, "1");

	/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
    AFNDInsertaEstado(p_afnd,"q0",INICIAL);
    AFNDInsertaEstado(p_afnd,"q1",NORMAL);
    AFNDInsertaEstado(p_afnd,"q2",NORMAL);
    AFNDInsertaEstado(p_afnd,"q3",NORMAL);
    AFNDInsertaEstado(p_afnd,"q4",FINAL);
    AFNDInsertaEstado(p_afnd,"q5",NORMAL);
    AFNDInsertaEstado(p_afnd,"q6",NORMAL);
    AFNDInsertaEstado(p_afnd,"q7",FINAL);

	/* DEFINICIÓN DE LAS TRANSICIONES NO LAMBDA */
    AFNDInsertaTransicion(p_afnd, "q1", "1", "q1");
    AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
    AFNDInsertaTransicion(p_afnd, "q3", "0", "q4");
    AFNDInsertaTransicion(p_afnd, "q5", "1", "q6");
    AFNDInsertaTransicion(p_afnd, "q6", "1", "q7");
    AFNDInsertaTransicion(p_afnd, "q7", "0", "q7");
    AFNDInsertaTransicion(p_afnd, "q7", "1", "q7");

    /** DEFINICIÓN DE LAS TRANSICIONES LAMBDA*/
    AFNDInsertaLTransicion(p_afnd, "q0", "q1");
    AFNDInsertaLTransicion(p_afnd, "q0", "q5");
    AFNDInsertaLTransicion(p_afnd, "q1", "q2");
    AFNDInsertaLTransicion(p_afnd, "q4", "q2");

    //AFNDImprime(stdout, p_afnd);

    /** INDUCIMOS EL RESTO DE TRANSICIONES LAMBDA*/
    AFNDCierraLTransicion(p_afnd);

    /* SE MUESTRA EL AFND DEFINIDO */
	AFNDImprime(stdout, p_afnd);


	/* DEFINICIÓN DE LA CADENA DE ENTRADA [ 1 1 1 1 0 0 ] */
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");

	/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */
	p_afnd = AFNDInicializaEstado(p_afnd);

	/* SE MUESTRA LA CADENA ACTUAL */
	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

/*********************************************************************************/

	/**INTRODUCIMOS NUEVA CADENA DE ENTRADA [ 1 0 0 0 0 0 0 ] */
	p_afnd = AFNDInicializaCadenaActual(p_afnd);

    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");

	p_afnd = AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDProcesaEntrada(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

/*********************************************************************************/

	/**NUEVA CADENA DE ENTRADA [ 1 1 0 0 0 ] */
	p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"0");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDProcesaEntrada(stdout,p_afnd);
    fprintf(stdout,"\n*********************************************\n");


/*********************************************************************************/

    /**NUEVA CADENA DE ENTRADA [ 0 1 0 1 0 1 0 1 ]*/
    p_afnd = AFNDInicializaCadenaActual(p_afnd);
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"1");
    AFNDInsertaLetra(p_afnd,"0");
    AFNDInsertaLetra(p_afnd,"1");

    p_afnd = AFNDInicializaEstado(p_afnd);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDProcesaEntrada(stdout,p_afnd);
    fprintf(stdout,"\n*********************************************\n");


/*********************************************************************************/

	/* SE LIBERAN TODOS LOS RECURSOS ASOCIADOS CON EL AFND */
	AFNDElimina(p_afnd);

	return EXIT_SUCCESS;
}