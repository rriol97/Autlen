/* ===================================================================
File: transicion.h
Authors: Ricardo Riol, Francisco de Vicente Lana

Main de pruebas numero 2. AFND propuesto en clase de teoria que 
reconoce palabras del alfabeto {a, b, c} tales que su lingitud es 
mayor que uno y  si aparece la c es tan solo al principio y/o al final.
Prueba el no determinismo
=================================================================== */
#include <stdio.h>
#include "afnd.h"

int main(int argc, char **argv)
{
	/* DECLARACIÓN DE UN PUNTERO A UN AFND */
	AFND *p_afnd;

	/* INICIALIZACIÓN DE UN NUEVO AFND */
	p_afnd = AFNDNuevo("af1", 3, 3);

	/* DEFINICIÓN DEL ALFABETO DEL AFND */
	AFNDInsertaSimbolo(p_afnd, "a");
	AFNDInsertaSimbolo(p_afnd, "b");
	AFNDInsertaSimbolo(p_afnd, "c");

	/* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", FINAL);

	/* DEFINICIÓN DE LAS TRANSICIONES */
	AFNDInsertaTransicion(p_afnd, "q0", "a", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "b", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "c", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "a", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "b", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "a", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "b", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "c", "q2");

	/* SE MUESTRA EL AFND DEFINIDO */
	fprintf(stdout, "\n****************** AFND *********************\n");
	AFNDImprime(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	/* DEFINICIÓN DE LA CADENA DE ENTRADA */
	p_afnd = AFNDInsertaLetra(p_afnd, "c");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "c");

	/* SE ESTABLECE COMO ESTADO ACTUAL DEL AUTÓMATA EL INICIAL */
	AFNDInicializaEstado(p_afnd);

	/* SE MUESTRA LA CADENA ACTUAL */
	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	/* SE PROCESA LA CADENA DE ENTRADA ACTUAL */
	AFNDProcesaEntrada(stdout, p_afnd);

	/* palabra 2 (aceptada)---------------------------*/
	p_afnd = AFNDInsertaLetra(p_afnd, "c");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");

	AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

	/* palabra 3 (rechazada)---------------------------*/
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "c");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");
	p_afnd = AFNDInsertaLetra(p_afnd, "b");
	p_afnd = AFNDInsertaLetra(p_afnd, "a");

	AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

	/* palabra 4 (rechazada)---------------------------*/
	p_afnd = AFNDInsertaLetra(p_afnd, "a");

	AFNDInicializaEstado(p_afnd);

	fprintf(stdout, "\n**************** PROCESA CADENA *************\n");
	AFNDImprimeCadenaActual(stdout, p_afnd);
	fprintf(stdout, "\n*********************************************\n");

	AFNDProcesaEntrada(stdout, p_afnd);

	/* SE LIBERAN TODOS LOS RECURSOS ASOCIADOS CON EL AFND */
	AFNDElimina(p_afnd);

	return 0;
}