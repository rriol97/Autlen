/* ===================================================================
File: transicion.h
Authors: Ricardo Riol, Francisco de Vicente Lana

Modulo que define el TAD automata finito no determinista.
=================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* 
nombre: AFNDInsertaSimbolo
desc: inserta un nuevo simbolo que maneja el afnd
args:
    -afnd: automata a modificar
    -sim: simbolo a introducir
retorno: -
*/
void AFNDInsertaSimbolo(AFND* afnd, char* sim);

/* 
nombre: AFNDInsertaEstado
desc: anade un nuevo estado al automata
args:
    -afnd: automata a modificar
    -nombre: nombre del estado
    -tipo: tipo del estado a anadir
retorno: -
*/
void AFNDInsertaEstado(AFND* afnd, char* nombre, int tipo);

/* 
nombre: AFNDInsertaTransicion
desc: anade una transicion al automata
args:
    -afnd: automata a modificar
    -nombreEstadoSalida: nombre del estado origen
    -nombreSim: nombre del simbolo a anadir
    -nombreEstadoLlegada: nombre del estado distino
retorno: -
*/
void AFNDInsertaTransicion(AFND* afnd, char* nombreEstadoSalida, char* nombreSim, char* nombreEstadoLlegada);

/* 
nombre: AFNDImprime
desc: imprime informacion del automata
args:
    -f: fichero de impresion
    -afnd: automata a imprimir
retorno: -
*/
void AFNDImprime(FILE *f, AFND* afnd);

/* 
nombre: AFNDInsertaLetra
desc: inserta una letra a la cadena de entrada
args:
    -afnd: automata a modificar
    -nombreLetra: nombre del simbolo a introducir
retorno: puntero al automata
*/
AFND* AFNDInsertaLetra(AFND* afnd, char* nombreLetra);

/* 
nombre: AFNDInicializaEstado
desc: Establece al estado INICIAL como el actual
args:
    -afnd: automata a modificar
retorno: -
*/
void AFNDInicializaEstado(AFND* afnd);

/* 
nombre: AFNDImprimeCadenaActual
desc: imprime la cadena entrante establecida
args:
    -f: fichero de impresion
    -afnd: automata a modificar
retorno: -
*/
void AFNDImprimeCadenaActual(FILE* f, AFND* afnd);

/* 
nombre: AFNDProcesaEntrada
desc: algoritmo para procesar un afnd
args:
    -f: fichero para mostrar el desarrollo
    -afnd: automata a imprimir
retorno: -
*/
void AFNDProcesaEntrada(FILE* f, AFND* afnd);

/* 
nombre: AFNDElimina
desc: libera los recursos reservados para el afnd
args:
    -afnd: automata a eliminar
retorno: -
*/
void AFNDElimina(AFND* afnd);