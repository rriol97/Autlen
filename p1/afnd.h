/* ===================================================================
File: transicion.h
Authors: Ricardo Riol, Francisco de Vicente Lana

Modulo que define el TAD automata finito no determinista.
=================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include "estado.h"
#include "conjunto_simbolos.h"
#include "transicion.h"

typedef struct _AFND AFND;

/* 
nombre: AFNDNuevo
desc: crea un AFND
args:
    -nombre: nombre del AFND
    -nest: numero de estados
    -nsim: numero simbolos
retorno: retorno al AFND creado
*/
AFND* AFNDNuevo(char* nombre, int nest, int nsim);


void AFNDInsertaSimbolo(AFND* afnd, char* sim);

void AFNDInsertaEstado(AFND* afnd, char* nombre, int tipo);

void AFNDInsertaTransicion(AFND* afnd, char* nombreEstadoSalida, char* nombreSim, char* nombreEstadoLlegada);

void AFNDImprime(FILE *f, AFND* afnd);

void AFNDInsertaLetra(AFND* afnd, char* nombreLetra);

/*
Estado actual a INICIAL
*/
void AFNDInicializaEstado(AFND* afnd);

void AFNDImprimeCadenaActual(FILE* f, AFND* afnd);

void AFNDProcesaEntrada(FILE* f, AFND* afnd);

void AFNDElimina(AFND* afnd);