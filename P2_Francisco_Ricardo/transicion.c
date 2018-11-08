/* ===================================================================
File: transicion.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Módulo que implementa el TAD Transicion. Se implementa como una tabla.
=================================================================== */

#include "transicion.h"

/** Estructura de estado*/
struct _Transicion
{
	int ***transiciones;
	int dim_matriz;
	int num_tablas;

	int nsim;
	int nest;
	char **simbolos;
	char **estados;
};

/* Declaracion funciones privadas */
int mapear_estado(Transicion *t, char *est);
int mapear_simbolo(Transicion *t, char *sim);
int *transicion_inducir_aux(Transicion *t, int sim, int estado, int *estados_accesibles, int *num);

/** Funciones */

/**Creamos e inicializamos una transicion nueva*/
Transicion *transicion_create(int num_simb, int num_estados)
{
	int i, k, j;
	Transicion *trans = NULL;
	num_simb++; /* Capa adicional para lambdas */

	if (num_estados == 0 || num_simb == 0)
	{
		return NULL;
	}

	trans = (Transicion *)malloc(sizeof(Transicion));
	if (!trans)
	{
		return NULL;
	}

	/* Tabla de transiciones */
	trans->transiciones = (int ***)malloc(sizeof(int **) * (num_simb));
	if (!trans->transiciones)
	{
		free(trans);
		return NULL;
	}

	for (i = 0; i < num_simb; i++)
	{
		trans->transiciones[i] = (int **)malloc(sizeof(int *) * num_estados);

		if (!trans->transiciones[i])
		{
			for (k = 0; k < i; k++)
			{
				free(trans->transiciones[k]);
			}
			return NULL;
		}
	}

	for (k = 0; k < num_simb; k++)
	{
		for (i = 0; i < num_estados; i++)
		{
			trans->transiciones[k][i] = (int *)malloc(sizeof(int) * num_estados);

			if (!trans->transiciones[k][i])
			{
				for (k = 0; k < num_simb; k++)
				{
					for (j = 0; j < i; j++)
					{
						free(trans->transiciones[k][j]);
					}
				}
				return NULL;
			}
		}
	}

	for (k = 0; k < num_simb; k++)
	{
		for (i = 0; i < num_estados; i++)
		{
			for (j = 0; j < num_estados; j++)
			{
				trans->transiciones[k][i][j] = NO_EXISTE;
			}
		}
	}

	/** Inicializamos el la estrcutura de transicion*/
	trans->dim_matriz = num_estados;
	trans->num_tablas = num_simb;

	/* Mapeo de estados y simbolos */
	trans->simbolos = (char **)malloc(sizeof(char *) * trans->num_tablas);
	if (!trans->simbolos)
	{
		// TODO: borrar todo
		return NULL;
	}
	for (i = 0; i < num_simb; i++)
	{
		trans->simbolos[i] = (char *)malloc(sizeof(char) * TAM);
		if (!trans->simbolos[i])
		{
			for (j = 0; j < i; j++)
			{
				free(trans->simbolos[j]);
			}
			return NULL;
		}
	}
	for (i = 0; i < num_simb; i++)
	{
		strcpy(trans->simbolos[i], "");
	}

	trans->estados = (char **)malloc(sizeof(char *) * num_estados);
	if (!trans->estados)
	{
		// TODO: borrar todo
		return NULL;
	}
	for (i = 0; i < num_estados; i++)
	{
		trans->estados[i] = (char *)malloc(sizeof(char) * TAM);
		if (!trans->estados[i])
		{
			for (j = 0; j < i; j++)
			{
				// TODO: borrar todo
				free(trans->estados[j]);
			}
			return NULL;
		}
	}
	for (i = 0; i < num_estados; i++)
	{
		strcpy(trans->estados[i], "");
	}

	trans->nsim = 0;
	trans->nest = 0;

	return trans;
}

/** Liberamos la memoria de una transicion*/
void transicion_destroy(Transicion *transicion)
{
	int i, k;

	if (!transicion)
	{
		return;
	}

	for (k = 0; k < transicion->num_tablas; k++)
	{
		for (i = 0; i < transicion->dim_matriz; i++)
		{
			free(transicion->transiciones[k][i]);
		}
	}

	for (k = 0; k < transicion->num_tablas; k++)
	{
		free(transicion->transiciones[k]);
	}

	free(transicion->transiciones);

	/* Mapeo simbolos y estdos */
	for (i = 0; i < transicion->num_tablas; i++)
	{
		free(transicion->simbolos[i]);
	}
	free(transicion->simbolos);

	for (i = 0; i < transicion->dim_matriz; i++)
	{
		free(transicion->estados[i]);
	}
	free(transicion->estados);

	free(transicion);
	return;
}

/**Obtenemos el valor de la transicion*/
int get_valor_transicion(Transicion *trans, char *simbolo, char *estado1, char *estado2)
{
	int sim, est0, estf;

	if (!simbolo || !estado1 || !estado2)
	{
		return ERR;
	}

	sim = mapear_simbolo(trans, simbolo);
	est0 = mapear_estado(trans, estado1);
	estf = mapear_estado(trans, estado2);

	if (sim == ERR || est0 == ERR || estf == ERR)
	{
		return ERR;
	}

	return trans->transiciones[sim][est0][estf];
}

/**Establecemos el valor de la transicion*/
void set_valor_transicion(Transicion *trans, char *simbolo, char *estado1, char *estado2)
{
	int sim, est0, estf;

	if (!trans || !simbolo || !estado1 || !estado2)
	{
		return;
	}

	sim = mapear_simbolo(trans, simbolo);
	est0 = mapear_estado(trans, estado1);
	estf = mapear_estado(trans, estado2);

	if (sim == ERR || est0 == ERR || estf == ERR)
	{
		return;
	}

	trans->transiciones[sim][est0][estf] = EXISTE;

	return;
}

/**Imprimir tabla de simbolos*/
void transicion_print(AFND *afnd, FILE *f, Transicion *transicion)
{
	int i, j, k;
	int tipo, len;
	char *nombre;

	if (!f || !transicion)
	{
		return;
	}
	if (!transicion->nest || !transicion->nsim)
	{
		fprintf(f, "-\n");
	}

	/* Impresion de cada tabla, una por simbolo */
	for (k = 0; k < transicion->nsim; k++)
	{
		/* Impresion cabecera */
		nombre = transicion->simbolos[k];
		len = strlen(nombre) + 2;
		fprintf(f, "\n\t\t'%s'", nombre);
		for (j = 0; j < ANCHO - len; j++) {
			fprintf(f, " ");
		}
		fprintf(f, "|");
		for (i = 0; i < transicion->nest; i++)
		{
			fprintf(f, " ");
			nombre = transicion->estados[i];
			len = strlen(nombre);
			tipo = get_tipo_estado(get_estado_from_name(afnd, nombre));
			if (tipo == INICIAL || tipo == INICIAL_y_FINAL) {
				fprintf(f, "->");
				len += 2;
			}

			if (len < 6) {
				fprintf(f, "%s", nombre);
			} else {
				fprintf(f, "%.3s", nombre);
				len -= strlen(nombre) - 3;
			}
			if (tipo == FINAL || tipo == INICIAL_y_FINAL) {
				fprintf(f, "*");
				len++;
			}
			for (j = 0; j < ANCHO - len; j++) {
				fprintf(f, " ");
			}
		}
		/* Impresion separador */
		fprintf(f, "\n\t\t------|");
		for (j = 0; j < transicion->nest; j++) {
			fprintf(f, "-------");
		}
		fprintf(f, "\n");
		/* Impresion de cada fila, una por estado */
		for (i = 0; i < transicion->nest; i++)
		{
			nombre = transicion->estados[i];
			len = strlen(nombre);
			tipo = get_tipo_estado(get_estado_from_name(afnd, nombre));

			fprintf(f, "\t\t");
			if (tipo == INICIAL || tipo == INICIAL_y_FINAL) {
				fprintf(f, "->");
				len += 2;
			}
			if (len < 6) {
				fprintf(f, "%s", nombre);
			} else {
				fprintf(f, "%.3s", nombre);
				len -= strlen(nombre) - 3;
			}
			if (tipo == FINAL || tipo == INICIAL_y_FINAL) {
				fprintf(f, "*");
				len++;
			}
			for (j = 0; j < ANCHO - len; j++) {
				fprintf(f, " ");
			}
			fprintf(f, "|");

			for (j = 0; j < transicion->nest; j++)
			{
				fprintf(f, "  %d    ", transicion->transiciones[k][i][j]);
			}
			fprintf(f, "\n");
		}
	}

	return;
}

void transicion_inducir(Transicion *t)
{
	int i, j, sim, num;
	int estados_accesibles[t->nest * t->nest];
	int *estados_actualizados = NULL;

	sim = mapear_simbolo(t, LAMBDA);

	if (!t)
	{
		return;
	}

	for (i = 0; i < t->nest; i++)
	{
		estados_actualizados = transicion_inducir_aux(t, sim, i, estados_accesibles, &num);
		for (j = 0; j < num; j++)
		{
			if (i != estados_actualizados[j])
			{
				t->transiciones[sim][i][estados_actualizados[j]] = EXISTE;
			}
		}
	}

	return;
}

/* --------------------- FUNCIONES PRIVADAS ---------------------- */

//Da todas las transiciones lambda del estado
int *transicion_inducir_aux(Transicion *t, int sim, int estado, int *estados_accesibles, int *num)
{
	int i = 0, pos = 0, j;

	if (!t)
	{
		return NULL;
	}

	//Metemos el estado que nos pasan como argumento
	estados_accesibles[0] = estado;
	pos += 1;

	while (i < pos)
	{
		for (j = 0; j < t->nest; j++)
		{
			if (t->transiciones[sim][estados_accesibles[i]][j] == EXISTE && estados_accesibles[i] != j)
			{
				estados_accesibles[pos] = j;
				pos += 1;
			}
		}
		i += 1;
	}

	*(num) = pos;

	return estados_accesibles;
}

int mapear_simbolo(Transicion *t, char *sim)
{
	int i;

	if (!t || !sim || t->nsim > t->num_tablas)
	{
		return ERR;
	}

	for (i = 0; i < t->nsim; i++)
	{
		if (strcmp(sim, t->simbolos[i]) == 0)
		{
			return i;
		}
	}
	strcpy(t->simbolos[t->nsim], sim);
	t->nsim++;

	return t->nsim - 1;
}

int mapear_estado(Transicion *t, char *est)
{
	int i;

	if (!t || !est || t->nest > t->dim_matriz)
	{
		return ERR;
	}

	for (i = 0; i < t->nest; i++)
	{
		if (strcmp(est, t->estados[i]) == 0)
		{
			return i;
		}
	}
	strcpy(t->estados[t->nest], est);
	t->nest++;

	return t->nest - 1;
}