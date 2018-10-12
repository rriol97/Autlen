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
struct _AFND {
	char *nombre;
    int nest;
    Estado** estados;
    int nsim;
    Conjunto_simbolos* alfabeto;
    Transicion* trans;
    Conjunto_simbolos* entrada;
    Estado* estadoActual;
};
*/

/* 
nombre: AFNDNuevo
desc: crea un AFND
args:
    -nombre: nombre del AFND
    -nest: numero de estados
    -nsim: numero simbolos
*/
AFND* AFNDNuevo(char* nombre, int nest, int nsim);


void AFNDInsertaSimbolo(AFND* afnd, char* sim);

void AFNDInsertaEstado(AFND* afnd, char* nombre, int tipo);

void AFNDInsertaTransicion(AFND* afnd, char* nombreEstadoSalida, char* nombreSim, char* nombreEstadoLlegada);

void AFNDImprime(FILE *f, AFND* afnd);

AFND* AFNDInsertaLetra(AFND* afnd, char* nombreLetra);

/*
Estado actual a INICIAL
*/
void AFNDInicializaEstado(AFND* afnd);

void AFNDImprimeCadenaActual(FILE* f, AFND* afnd);

void AFNDProcesaEntrada(FILE* f, AFND* afnd);

void AFNDElimina(AFND* afnd);