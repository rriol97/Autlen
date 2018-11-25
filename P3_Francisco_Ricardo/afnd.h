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

#define SIN_INICIALIZAR -1
#define TRUE 1
#define FALSE 0
#define NEST_BASICO 2
#define NEST_VACIO 1
#define NSIM_BASICO 1
#define NSIM_VACIO 0

#define MAX 64

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
AFND *AFNDNuevo(char *nombre, int nest, int nsim);

/* 
nombre: AFNDElimina
desc: libera los recursos reservados para el afnd
args:
    -afnd: automata a eliminar
retorno: -
*/
void AFNDElimina(AFND *afnd);

/* 
nombre: AFNDInsertaSimbolo
desc: inserta un nuevo simbolo que maneja el afnd
args:
    -afnd: automata a modificar
    -sim: simbolo a introducir
retorno: -
*/
void AFNDInsertaSimbolo(AFND *afnd, char *sim);

/* 
nombre: AFNDInsertaEstado
desc: anade un nuevo estado al automata
args:
    -afnd: automata a modificar
    -nombre: nombre del estado
    -tipo: tipo del estado a anadir
retorno: -
*/
void AFNDInsertaEstado(AFND *afnd, char *nombre, int tipo);

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
void AFNDInsertaTransicion(AFND *afnd, char *nombreEstadoSalida, char *nombreSim, char *nombreEstadoLlegada);

/* 
nombre: AFNDImprime
desc: imprime informacion del automata
args:
    -f: fichero de impresion
    -afnd: automata a imprimir
retorno: -
*/
void AFNDImprime(FILE *f, AFND *afnd);

/* 
nombre: AFNDInsertaLetra
desc: inserta una letra a la cadena de entrada
args:
    -afnd: automata a modificar
    -nombreLetra: nombre del simbolo a introducir
retorno: puntero al automata
*/
AFND *AFNDInsertaLetra(AFND *afnd, char *nombreLetra);

/* 
nombre: AFNDInicializaEstado
desc: Establece al estado INICIAL como el actual
args:
    -afnd: automata a modificar
retorno: -
*/
AFND *AFNDInicializaEstado(AFND *afnd);

/* 
nombre: AFNDImprimeCadenaActual
desc: imprime la cadena entrante establecida
args:
    -f: fichero de impresion
    -afnd: automata a modificar
retorno: -
*/
void AFNDImprimeCadenaActual(FILE *f, AFND *afnd);

/* 
nombre: AFNDProcesaEntrada
desc: algoritmo para procesar un afnd
args:
    -f: fichero para mostrar el desarrollo
    -afnd: automata a procesar
retorno: -
*/
int AFNDProcesaEntrada(FILE *f, AFND *afnd);

/* 
nombre: AFNDInsertaLTransicion
desc: permite insertar transiciones lambda
args:
    -afnd: automata a modificar
    -q0: estado origen
    -q1: estado destino
retorno: -
*/
AFND *AFNDInsertaLTransicion(AFND *afnd, char *q0, char *qf);

/* 
nombre: AFNDCierraLTransicion
desc: induce las obtenidas por transitividad
args:
    -afnd: automata a modificar
retorno: -
*/
AFND *AFNDCierraLTransicion(AFND *afnd);

/* 
nombre: AFNDInicializaCadenaActual
desc: prepara el afnd para introducir una nueva cadena
args:
    -afnd: automata a preparar
retorno: puntero a AFND
*/
AFND *AFNDInicializaCadenaActual(AFND *afnd);

/* 
nombre: get_estado_from_name
desc: devuelve un estado del afnd a partir de su nombre
args:
    -afnd: automata cuyo estado se quiere obtener
    -name: nombre del estado en cuestion
retorno: estado encontrado o NULL si no se encuentra
*/
Estado *get_estado_from_name(AFND *afnd, char *name);

/* 
nombre: sin_repetidos
desc: indica si cierto entero se encuentra en un array de enteros
args:
    -actuales_aux: array de enteros donde buscar
    -id_aux: entero a buscar
    -tam: longitud del array
retorno: FALSE si id_aux esta en actuales_aux, TRUE en caso contrario
*/
int sin_repetidos(int *actuales_aux, int id_aux, int tam);

/* -------------- Funciones para la P3 ------------------- */

/* 
nombre: AFND1ODeSimbolo
desc: crea un automata basico que reconozco un unico simbolo
args:
    -sim: simbolo a reconocer
retorno: afnd creado, NULL en caso de error
*/
AFND* AFND1ODeSimbolo(char* sim);


AFND* AFND1OUne(AFND* afnd1, AFND* afnd2);
AFND* AFND1OConcatena(AFND* afnd1, AFND* afnd2);
AFND* AFND1OEstrella(AFND* afnd);

/* Combierte afnd a la especificacion 1O */
AFND * AFNDAAFND1O(AFND * p_afnd);