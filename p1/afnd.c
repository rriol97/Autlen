/* ===================================================================
File: maquina_estados.c
Authors: Ricardo Riol, Francisco de Vicente Lana

Modulo para el TAD automata finito no determinista.
=================================================================== */
#include "afnd.h"

/** Estructura del AFND*/
struct _AFND {
	char *nombre;
    /* ESTADOS */
    int idEstados;
    int nest;
    Estado** estados;
    Estado* estadoActual;
    /* SIMBOLOS Y CADENAS */
    int nsim;
    Conjunto_simbolos* alfabeto;
    Conjunto_simbolos* entrada;
    /* TRANSICIONES */
    Transicion* trans;
    
};

/* Funciones del AFND */

AFND* AFNDNuevo(char* nombre, int nest, int nsim) {
    AFND* afnd = NULL;

    if (!nombre || nest < 1 || nsim < 1) {
        return NULL;
    }

    afnd = (AFND *)malloc(sizeof(AFND));
    if (!afnd) {
        return NULL;
    }

    /* nombre */
    afnd->nombre = (char *)malloc(sizeof(char) * (strlen(nombre) + 1));
    if (!afnd->nombre) {
        free(afnd);
        return NULL;
    }
    if (!strcpy(afnd->nombre, nombre)) {
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }

    /* nest, nsim y idEstados */
    afnd->nest = nest;
    afnd->nsim = nsim;
    afnd->idEstados = 1;

    /* estados y alfabeto */
    afnd->estados = (Estado **)malloc(sizeof(Estado*) * nest);
    if (!afnd->estados) {
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }
    afnd->alfabeto = conjunto_simbolos_create("A");
    if (afnd->alfabeto) {
        free(afnd->estados);
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }

    /* Transiciones, Entreda y Estado actual */
    afnd->estadoActual = NULL;
    afnd->trans = NULL;
    afnd->entrada = conjunto_simbolos_create(CADENA);

    return afnd;
}

void AFNDElimina(AFND* afnd) {
    int i; 

    if (!afnd) {
        return;
    }

    free(afnd->nombre);

    /* Liberacion estados */
    for (i = 0; i < afnd->nest; i++) {
        estado_destroy(afnd->estados[i]);
    }   
    estado_destroy(afnd->estadoActual);

    /* Liberacion de simbolos y cadena */
    conjunto_simbolos_destroy(afnd->alfabeto);
    conjunto_simbolos_destroy(afnd->entrada);

    /* Liberacion transiciones */
    transicion_destroy(afnd->trans);

    return;
}

void AFNDInsertaSimbolo(AFND* afnd, char* sim) {
    if (!afnd || !sim) {
        return;
    }
    insert_simbolo(afnd->alfabeto, sim);
}

void AFNDInsertaEstado(AFND* afnd, char* nombre, int tipo) {
    if (!afnd || !nombre || tipo < INICIAL || tipo > FINAL) {
        return;
    }
    
    afnd->idEstados = afnd->idEstados + 1;
    afnd->estados[afnd->idEstados] = estado_create(nombre, tipo, afnd->idEstados);

    return;
}

void AFNDInsertaTransicion(AFND* afnd, char* nombreEstadoSalida, char* nombreSim, char* nombreEstadoLlegada);

void AFNDImprime(FILE *f, AFND* afnd) {
    int i;
    char aux[32]; // TODO: revisar

    if (!afnd) {
        fprintf(f, "Automata vacio\n");
    }

    fprintf(f, "{AFND: %s\n", afnd->nombre);

    print_conjunto_simbolos(f, afnd->alfabeto);

    fprintf(f, "num_estados %d\n", afnd->idEstados);

    fprintf(f, "\tEstados: %s,", afnd->estados[0]);
    for (i = 1; i < afnd->nest; i++) {
        // Func imprimir, solo nombre
        strcpy(aux, estado_imprimir(afnd->estados[i]));
        fprintf(f, ", %s", aux);
    }

}

AFND* AFNDInsertaLetra(AFND* afnd, char* nombreLetra) {
    if (!afnd || !nombreLetra) {
        return NULL;
    }

    insert_simbolo(afnd->entrada, nombreLetra);
    return afnd;
}

/*
Estado actual a INICIAL
*/
void AFNDInicializaEstado(AFND* afnd) {
    int i;

    if (!afnd) {
        return;
    }

    for (i = 0; i < afnd->nest; i++) {
        if (get_tipo_estado(afnd->estados[i]) == INICIAL) {
            afnd->estadoActual = afnd->estados[i];
            break;
        }
    }
}

void AFNDImprimeCadenaActual(FILE* f, AFND* afnd) {
    if (!f || !afnd) {
        return;
    }

    print_conjunto_simbolos(afnd->entrada);

    return;
}

void AFNDProcesaEntrada(FILE* f, AFND* afnd);