#include "estado.h"

/** Estructura de estado*/
struct _Estado {
    char *nombre;
    int number;
    TIPO tipo;
};

/** Funciones a implementar */
Estado* estado_create(char *nombre, TIPO tipo) {
	Estado *estado = NULL;

	if (!nombre) {
		return NULL;
	}

	estado = (Estado*) malloc (sizeof(Estado)); /**Reservamos memoria para un estado*/

	strcpy(estado->nombre, nombre);
	estado->tipo = tipo;

	return estado;
}

void estado_destroy(Estado *estado){

	if (!estado){
		return;
	}

	free(estado);
	return;
}

char* get_name_estado(Estado* estado){

}