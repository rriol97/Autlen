/* ===================================================================
File: conjunto_simbolos.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Implementación de un conjunto de simbolos. Nos servirá para poder manejar alfabeto y palabras.
=================================================================== */
#include "conjunto_simbolos.h"

/** Estructura de conjunto_simbolos*/
struct _Conjunto_simbolos
{
	char *nombre;
	char **simbolos;
	int nsym;
};

/** Funciones a implementar */

/**Creamos e inicializamos un conjunto vacio nuevo*/
Conjunto_simbolos *conjunto_simbolos_create(char *nombre)
{
	Conjunto_simbolos *conjunto_simbolos = NULL;

	if (!nombre)
	{
		return NULL;
	}

	conjunto_simbolos = (Conjunto_simbolos *)malloc(sizeof(Conjunto_simbolos));
	if (!conjunto_simbolos)
	{
		return NULL;
	}

	conjunto_simbolos->nombre = (char *)malloc(sizeof(char) * strlen(nombre) + 1);
	if (!conjunto_simbolos->nombre)
	{
		free(conjunto_simbolos);
		return NULL;
	}

	if (!strcpy(conjunto_simbolos->nombre, nombre))
	{
		free(conjunto_simbolos->nombre);
		free(conjunto_simbolos);
		return NULL;
	}
	conjunto_simbolos->simbolos = NULL;
	conjunto_simbolos->nsym = 0;

	return conjunto_simbolos;
}

/** Insertamos u síbolo nuevo en el conjunto_simbolos*/
void insert_simbolo(Conjunto_simbolos *conjunto_simbolos, char *sym)
{
	if (!conjunto_simbolos || !sym)
	{
		return;
	}

	/** Si es el primer simbolo */
	if (conjunto_simbolos->nsym == 0)
	{
		conjunto_simbolos->simbolos = (char **)malloc(sizeof(char *));

		if (!conjunto_simbolos->simbolos)
		{
			return;
		}
	}

	/**Si ya hay simbolos en el conjunto_simbolos */
	else
	{
		conjunto_simbolos->simbolos = (char **)realloc(conjunto_simbolos->simbolos, sizeof(char *) * 2 * (conjunto_simbolos->nsym + 1));

		if (!conjunto_simbolos->simbolos)
		{
			return;
		}
	}

	conjunto_simbolos->simbolos[conjunto_simbolos->nsym] = (char *)malloc(sizeof(char) * strlen(sym) + 1);

	if (!conjunto_simbolos->simbolos[conjunto_simbolos->nsym])
	{
		return;
	}

	strcpy(conjunto_simbolos->simbolos[conjunto_simbolos->nsym], sym);
	conjunto_simbolos->nsym++;

	return;
}

/**Liberamos la memoria de un conjunto_simbolos*/
void conjunto_simbolos_destroy(Conjunto_simbolos *conjunto_simbolos)
{
	int i;

	if (!conjunto_simbolos)
	{
		return;
	}

	free(conjunto_simbolos->nombre);

	if (conjunto_simbolos->nsym == 0)
	{
		free(conjunto_simbolos);
		return;
	}

	for (i = 0; i < conjunto_simbolos->nsym; i++)
	{
		free(conjunto_simbolos->simbolos[i]);
	}

	free(conjunto_simbolos->simbolos);
	free(conjunto_simbolos);
}

char **get_simbolos(Conjunto_simbolos *conjunto_simbolos)
{

	if (!conjunto_simbolos)
	{
		return NULL;
	}

	return conjunto_simbolos->simbolos;
}

/**Obtener el nombre del conjunto_simbolos*/
char *get_nombre_conjunto(Conjunto_simbolos *conjunto_simbolos)
{

	if (!conjunto_simbolos)
	{
		return NULL;
	}
	return conjunto_simbolos->nombre;
}

/** Ver si un símbolo esta contenido en el conjunto **/
int is_in_conjunto_simbolos(Conjunto_simbolos *conjunto_simbolos, char *sym)
{
	int i;

	if (conjunto_simbolos->nsym == 0)
	{
		return 0;
	}

	else
	{
		for (i = 0; i < conjunto_simbolos->nsym; i++)
		{
			if (strcmp(conjunto_simbolos->simbolos[i], sym) == 0)
			{
				return 1;
			}
		}
	}

	return 0;
}

/**Obtener el numero de simbolos del conjunto_simbolos*/
int get_num_simbolos(Conjunto_simbolos *conjunto_simbolos)
{

	if (!conjunto_simbolos)
	{
		return -1;
	}

	return conjunto_simbolos->nsym;
}

/** Función que nos facilitará la impresión de un conjunto_simbolos*/
void print_conjunto_simbolos(FILE *f, Conjunto_simbolos *conjunto_simbolos, int pos)
{
	int simbolo;

	if (conjunto_simbolos->nsym == 0)
	{
		fprintf(f, "-\n");
		return;
	}

	if (strcmp(conjunto_simbolos->nombre, "Cadena") == 0)
	{
		fprintf(f, "[(%d) ", conjunto_simbolos->nsym - pos);

		for (simbolo = pos; simbolo < conjunto_simbolos->nsym - 1; simbolo++)
		{
			printf("%s ", conjunto_simbolos->simbolos[simbolo]);
		}

		if (pos >= conjunto_simbolos->nsym)
		{
			fprintf(f, "]\n");
		}

		else
		{
			fprintf(f, "%s]\n", conjunto_simbolos->simbolos[conjunto_simbolos->nsym - 1]);
		}
	}

	else
	{
		//printf("Num_simbolos = %d\n", conjunto_simbolos->nsym);
		printf("{");

		for (simbolo = 0; simbolo < conjunto_simbolos->nsym - 1; simbolo++)
		{
			printf("%s,", conjunto_simbolos->simbolos[simbolo]);
		}

		printf("%s}\n", conjunto_simbolos->simbolos[conjunto_simbolos->nsym - 1]);
	}

	return;
}
