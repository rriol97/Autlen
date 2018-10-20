/* ===================================================================
File: transicion.h
Authors: Ricardo Riol, Francisco de Vicente Lana

Main de pruebas numero 2. AFND propuesto en clase de teoria que 
reconoce palabras binarias que contienen la subcadena '1010'.
Prueba un automata sencillo
=================================================================== */
#include <stdio.h>
#include "afnd.h"

int main(int argc, char **argv)
{
	/* DECLARACIÓN DE UN PUNTERO A UN AFND */
	AFND *p_afnd;

	/* INICIALIZACIÓN DE UN NUEVO AFND */
	p_afnd = AFNDNuevo("af1", 5, 2);

	/* DEFINICIÓN DEL ALFABETO DEL AFND */
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, "1");

	/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "qf", FINAL);

	/* DEFINICIÓN DE LAS TRANSICIONES */
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q2", "1", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "qf");
	AFNDInsertaTransicion(p_afnd, "q3", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "qf", "0", "qf");
	AFNDInsertaTransicion(p_afnd, "qf", "1", "qf");

	/* SE MUESTRA EL AFND DEFINIDO */
	fprintf(stdout, "\n****************** AFND *********************\n");
	AFNDImprime(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	/* DEFINICIÓN DE LA CADENA DE ENTRADA */
	p_afnd = AFNDInsertaLetra(p_afnd, "1");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "1");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");

	/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */
	AFNDInicializaEstado(p_afnd);

	/* SE MUESTRA LA CADENA ACTUAL */
	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	/* SE PROCESA LA CADENA DE ENTRADA ACTUAL */
	AFNDProcesaEntrada(stdout, p_afnd);

	/* palabra 2 (aceptada)---------------------------*/
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "1");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "1");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");

	AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

	/* palabra 3 (rechazada)---------------------------*/
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "1");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "1");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");
	p_afnd = AFNDInsertaLetra(p_afnd, "0");

	AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

	/* palabra 2 (rechazada)---------------------------*/
	p_afnd = AFNDInsertaLetra(p_afnd, "0");

	AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

	/* SE LIBERAN TODOS LOS RECURSOS ASOCIADOS CON EL AFND */
	AFNDElimina(p_afnd);

	return 0;
}