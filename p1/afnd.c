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

/** Funciones del AFND */
AFND* AFNDNuevo(char* nombre, int nest, int nsim) {
    AFND* afnd = NULL;
    int i;

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

    /* estados y alfabeto */
    afnd->nest = nest;
    afnd->nsim = nsim;
    afnd->idEstados = 0;

    afnd->estados = (Estado **)malloc(sizeof(Estado*) * nest);
    if (!afnd->estados) {
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }
    for (i = 0; i < nest; i++) {
        afnd->estados[i] = NULL;
    }

    afnd->alfabeto = conjunto_simbolos_create("A");
    if (!afnd->alfabeto) {
        free(afnd->estados);
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }

    /* Transiciones, Entreda y Estado actual */
    afnd->estadoActual = NULL;
    afnd->trans = transicion_create(afnd->nsim, afnd->nest);
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
        if (!afnd->estados[i]) {
            break;
        }
        estado_destroy(afnd->estados[i]);
    }   
    // estado_destroy(afnd->estadoActual); esta incluido arriba
    afnd->estadoActual = NULL;
    free(afnd->estados);

    /* Liberacion de simbolos y cadena */
    conjunto_simbolos_destroy(afnd->alfabeto);
    conjunto_simbolos_destroy(afnd->entrada);

    /* Liberacion transiciones */
    transicion_destroy(afnd->trans);

    free(afnd);

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
    
    afnd->estados[afnd->idEstados] = estado_create(nombre, tipo, afnd->idEstados);
    afnd->idEstados++;

    return;
}

void AFNDInsertaTransicion(AFND* afnd, char* nombreEstadoSalida, char* nombreSim, char* nombreEstadoLlegada) {
    
    if (!afnd || !nombreEstadoSalida || !nombreSim || !nombreEstadoLlegada) {
        return;
    }

    //Funcion para insertar transiciones?
    set_valor_transicion(afnd->trans, nombreSim, nombreEstadoSalida, nombreEstadoLlegada);

    return;
}

void AFNDImprime(FILE *f, AFND* afnd) {
    int i;

    if (!afnd) {
        fprintf(f, "AFND vacio\n");
        return;
    }

    fprintf(f, "{ AFND: %s\n", afnd->nombre);

    /* Estados */
    fprintf(f, "\tEstados [%d]: ", afnd->nest);
    if (afnd->idEstados == 0) {
        fprintf(f, "-\n");
    }
    else {
        print_estado(f, afnd->estados[0]);
        for (i = 1; i < afnd->nest; i++) {
            fprintf(f, ", ");
            print_estado(f, afnd->estados[i]);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "\tEstado actual: ");
    if (!afnd->estadoActual) {
        fprintf(f, "-");
    } else {
        print_estado(f, afnd->estadoActual);
    }
    fprintf(f, "\n");

    /* Alfabeto y cadena */
    fprintf(f, "\tAlfabeto [%d]: ", afnd->nsim);
    print_conjunto_simbolos(f, afnd->alfabeto);

    fprintf(f, "\tCadena entrada: ");
    print_conjunto_simbolos(f, afnd->entrada);

    /* Transiciones */
    fprintf(f, "\tTablas de transiciones: ");
    if (!afnd->trans) {
        fprintf(f, "-\n");
    }
    else {
        transicion_print(f, afnd->trans);
    }

    fprintf(f, "}\n");

    return;
}

AFND* AFNDInsertaLetra(AFND* afnd, char* nombreLetra) {
    if (!afnd || !nombreLetra) {
        return NULL;
    }

    insert_simbolo(afnd->entrada, nombreLetra);
    return afnd;
}


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

    printf("Cadena entrante:\n");
    print_conjunto_simbolos(f, afnd->entrada);

    return;
}

void AFNDProcesaEntrada(FILE* f, AFND* afnd) {
    if (!f || !afnd) {
        return;
    }

    return;
}