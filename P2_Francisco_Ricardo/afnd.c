/* ===================================================================
File: maquina_estados.c
Authors: Ricardo Riol, Francisco de Vicente Lana

Modulo para el TAD automata finito no determinista.
=================================================================== */
#include "afnd.h"

/** Estructura del AFND*/
struct _AFND
{
    char *nombre;
    /* ESTADOS */
    int idEstados;
    int nest;
    Estado **estados;
    int *id_actuales;
    int nactuales;
    /* SIMBOLOS Y CADENAS */
    int nsim;
    Conjunto_simbolos *alfabeto;
    Conjunto_simbolos *entrada;
    /* TRANSICIONES */
    Transicion *trans;
    int iteraciones;
};

/** Funciones privadas del modulo */
Estado *get_estado_from_id(AFND *afnd, int id);
int algun_actual_final(AFND *afnd);
void resetear_actuales(AFND *afnd, int *ids);
int sin_repetidos(int *actuales_aux, int id_aux, int tam);

/** Funciones del AFND */
AFND *AFNDNuevo(char *nombre, int nest, int nsim)
{
    AFND *afnd = NULL;
    int i;

    if (!nombre || nest < 1 || nsim < 1)
    {
        return NULL;
    }

    afnd = (AFND *)malloc(sizeof(AFND));
    if (!afnd)
    {
        return NULL;
    }

    /* nombre */
    afnd->nombre = (char *)malloc(sizeof(char) * (strlen(nombre) + 1));
    if (!afnd->nombre)
    {
        free(afnd);
        return NULL;
    }
    if (!strcpy(afnd->nombre, nombre))
    {
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }

    /* estados y alfabeto */
    afnd->nest = nest;
    afnd->nsim = nsim;
    afnd->idEstados = 0;

    afnd->estados = (Estado **)malloc(sizeof(Estado *) * nest);
    if (!afnd->estados)
    {
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }
    for (i = 0; i < nest; i++)
    {
        afnd->estados[i] = NULL;
    }

    afnd->alfabeto = conjunto_simbolos_create("A");
    if (!afnd->alfabeto)
    {
        free(afnd->estados);
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }

    /* Transiciones, Entreda y Estado actual */
    afnd->id_actuales = (int *)malloc(sizeof(int) * nest);
    if (!afnd->id_actuales)
    {
        free(afnd->alfabeto);
        free(afnd->estados);
        free(afnd->nombre);
        free(afnd);
        return NULL;
    }

    //resetear_actuales(afnd, afnd->id_actuales);

    afnd->trans = transicion_create(afnd->nsim, afnd->nest);
    afnd->entrada = conjunto_simbolos_create(CADENA);

    afnd->iteraciones = 0;
    afnd->nactuales = 0;

    return afnd;
}

void AFNDElimina(AFND *afnd)
{
    int i;

    if (!afnd)
    {
        return;
    }

    free(afnd->nombre);

    /* Liberacion estados */
    for (i = 0; i < afnd->nest; i++)
    {
        if (!afnd->estados[i])
        {
            break;
        }
        estado_destroy(afnd->estados[i]);
    }
    // estado_destroy(afnd->id_actuales); esta incluido arriba
    free(afnd->id_actuales);
    free(afnd->estados);

    /* Liberacion de simbolos y cadena */
    conjunto_simbolos_destroy(afnd->alfabeto);
    conjunto_simbolos_destroy(afnd->entrada);

    /* Liberacion transiciones */
    transicion_destroy(afnd->trans);

    free(afnd);

    return;
}

void AFNDInsertaSimbolo(AFND *afnd, char *sim)
{
    if (!afnd || !sim)
    {
        return;
    }
    insert_simbolo(afnd->alfabeto, sim);
}

void AFNDInsertaEstado(AFND *afnd, char *nombre, int tipo)
{
    if (!afnd || !nombre || tipo < INICIAL || tipo > FINAL)
    {
        return;
    }

    afnd->estados[afnd->idEstados] = estado_create(nombre, tipo, afnd->idEstados);
    afnd->idEstados++;

    return;
}

void AFNDInsertaTransicion(AFND *afnd, char *nombreEstadoSalida, char *nombreSim, char *nombreEstadoLlegada)
{

    if (!afnd || !nombreEstadoSalida || !nombreSim || !nombreEstadoLlegada)
    {
        return;
    }
    if (!strcmp(nombreSim, LAMBDA)) {
        frpintf(stderr, "No esta permitido el uso de simbolos llamados 'lambda'\n");
        return;
    }

    set_valor_transicion(afnd->trans, nombreSim, nombreEstadoSalida, nombreEstadoLlegada);

    return;
}

void AFNDImprime(FILE *f, AFND *afnd)
{
    int i;

    if (!afnd)
    {
        fprintf(f, "AFND vacio\n");
        return;
    }

    fprintf(f, "{ AFND: %s\n", afnd->nombre);

    /* Estados */
    fprintf(f, "\tEstados [%d]: ", afnd->nest);
    if (afnd->idEstados == 0)
    {
        fprintf(f, "-\n");
    }
    else
    {
        print_estado(f, afnd->estados[0]);
        for (i = 1; i < afnd->nest; i++)
        {
            fprintf(f, ", ");
            print_estado(f, afnd->estados[i]);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "\tEstados actuales: ");
    if (afnd->nactuales == 0)
    {
        fprintf(f, "-");
    }
    else
    {
        for (i = 0; i < afnd->nactuales; i++)
        {
            print_estado(f, get_estado_from_id(afnd, afnd->id_actuales[i]));
        }
    }
    fprintf(f, "\n");

    /* Alfabeto y cadena */
    fprintf(f, "\tAlfabeto [%d]: ", afnd->nsim);
    print_conjunto_simbolos(f, afnd->alfabeto, 0);

    fprintf(f, "\tCadena entrada: ");
    print_conjunto_simbolos(f, afnd->entrada, 0);

    /* Transiciones */
    fprintf(f, "\tTablas de transiciones: ");
    if (!afnd->trans)
    {
        fprintf(f, "-\n");
    }
    else
    {
        transicion_print(f, afnd->trans);
    }

    fprintf(f, "}\n");

    return;
}

AFND *AFNDInsertaLetra(AFND *afnd, char *nombreLetra)
{
    if (!afnd || !nombreLetra)
    {
        return NULL;
    }

    insert_simbolo(afnd->entrada, nombreLetra);
    return afnd;
}

void AFNDInicializaEstado(AFND *afnd)
{
    int i;

    if (!afnd)
    {
        return;
    }

    for (i = 0; i < afnd->nest; i++)
    {
        if (get_tipo_estado(afnd->estados[i]) == INICIAL || get_tipo_estado(afnd->estados[i]) == INICIAL_y_FINAL)
        {
            afnd->id_actuales[afnd->nactuales] = estado_get_id(afnd->estados[i]);
            afnd->nactuales++;
        }
    }
}

void AFNDImprimeCadenaActual(FILE *f, AFND *afnd)
{
    if (!f || !afnd)
    {
        return;
    }

    print_conjunto_simbolos(f, afnd->entrada, 0);

    return;
}

/* ---------------------------------------------------------------------------- */
int AFNDProcesaEntrada(FILE *f, AFND *afnd)
{
    int len_cadena, i, j, ret, cont = 0;
    int *actuales_aux;
    char **entrada = get_simbolos(afnd->entrada);
    char *entrada_actual;
    int id_aux;

    if (!f || !afnd)
    {
        fprintf(f, "Error: Error de fichero o de afnd\n");
        return FALSE;
    }

    //Longitud de la cadena  de entrada
    len_cadena = get_num_simbolos(afnd->entrada);

    while (afnd->nactuales > 0 && afnd->iteraciones < len_cadena)
    {

        fprintf(f, "ACTUALMENTE EN {%s", get_name_estado(get_estado_from_id(afnd, afnd->id_actuales[0])));
        for (i = 1; i < afnd->nactuales; i++)
        {
            fprintf(f, ", %s", get_name_estado(get_estado_from_id(afnd, afnd->id_actuales[i])));
        }
        fprintf(f, "}\n");

        print_conjunto_simbolos(f, afnd->entrada, afnd->iteraciones);

        actuales_aux = (int *)malloc(sizeof(int) * afnd->nest);
        if (!actuales_aux)
        {
            fprintf(f, "Error: Error en array auxiliar\n");
            return FALSE;
        }
        resetear_actuales(afnd, actuales_aux);

        entrada_actual = entrada[afnd->iteraciones];

        for (i = 0; i < afnd->nactuales; i++)
        {
            for (j = 0; j < afnd->nest; j++)
            {
                ret = get_valor_transicion(afnd->trans, entrada_actual, get_name_estado(get_estado_from_id(afnd, afnd->id_actuales[i])), get_name_estado(afnd->estados[j]));
                if (ret == EXISTE)
                {
                    id_aux = estado_get_id(afnd->estados[j]);
                    if (sin_repetidos(actuales_aux, id_aux, afnd->nactuales))
                    {
                        actuales_aux[cont] = id_aux;
                        cont += 1;
                    }
                }
            }
        }

        afnd->nactuales = cont;
        cont = 0;
        free(afnd->id_actuales);
        afnd->id_actuales = actuales_aux;

        actuales_aux = NULL;
        afnd->iteraciones++;
    }

    if (afnd->nactuales == 0)
    {
        fprintf(f, "ACABAMOS SIN ESTADOS FINALES ");
    }
    else
    {
        fprintf(f, "ACABAMOS EN {%s", get_name_estado(get_estado_from_id(afnd, afnd->id_actuales[0])));
        for (i = 1; i < afnd->nactuales; i++)
        {
            fprintf(f, ", %s", get_name_estado(get_estado_from_id(afnd, afnd->id_actuales[i])));
        }
    }

    fprintf(f, "}\n");
    print_conjunto_simbolos(f, afnd->entrada, afnd->iteraciones);

    ret = FALSE;
    if (afnd->iteraciones == len_cadena)
    {
        ret = algun_actual_final(afnd);
    }

    afnd->nactuales = 0;
    afnd->iteraciones = 0;
    conjunto_simbolos_destroy(afnd->entrada);
    afnd->entrada = conjunto_simbolos_create(CADENA);

    if (ret == TRUE)
    {
        fprintf(f, "> Cadena aceptada <\n");
    }
    else
    {
        fprintf(f, "> Cadena rechazada <\n");
    }

    return ret;
}
/* ---------------------------------------------------------------------------- */

AFND * AFNDInsertaLTransicion(AFND *afnd, char *q0, char *qf) {
    
    if (!afnd || !q0 || !qf) {
        return NULL;
    }

    set_valor_transicion(afnd->trans, LAMBDA, q0, qf);

    return afnd;
}


AFND * AFNDCierraLTransicion(AFND *afnd) {
    int i;
    char *nombre_estado;

    if (!afnd) {
        return NULL;
    }

    transicion_inducir(afnd->trans);

    for (i = 0; i < afnd->nest; i++) {
        nombre_estado = get_name_estado(afnd->estados[i]);
		set_valor_transicion(afnd->trans, LAMBDA, nombre_estado, nombre_estado);
	}


    return afnd;
}


AFND * AFNDInicializaCadenaActual(AFND* afnd) {

    if (!afnd) {
        return NULL;
    }

    return afnd;
}

/* -------------------- FUNCIONES PRIVADAS ----------------------------- */

Estado *get_estado_from_id(AFND *afnd, int id)
{
    if (!afnd || id < 0 || id > afnd->nest)
    {
        return NULL;
    }

    if (afnd->estados[id] != NULL)
    {
        return afnd->estados[id];
    }
    return NULL;
}

int algun_actual_final(AFND *afnd)
{
    int i;

    if (!afnd)
    {
        return FALSE;
    }

    for (i = 0; i < afnd->nactuales; i++)
    {
        if (get_tipo_estado(get_estado_from_id(afnd, afnd->id_actuales[i])) == FINAL ||
            get_tipo_estado(get_estado_from_id(afnd, afnd->id_actuales[i])) == INICIAL_y_FINAL)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void resetear_actuales(AFND *afnd, int *ids)
{
    int i;

    if (!ids)
    {
        return;
    }

    for (i = 0; i < afnd->nactuales; i++)
    {
        ids[i] = SIN_INICIALIZAR;
    }

    return;
}

int sin_repetidos(int *actuales_aux, int id_aux, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        if (actuales_aux[i] == id_aux)
        {
            return FALSE;
        }
    }
    return TRUE;
}
