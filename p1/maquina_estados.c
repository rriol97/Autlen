/* ===================================================================
File: maquina_estados.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include "estado.h"
#include "conjunto_simbolos.h"
#include <stdio.h>


int main(){
	Estado *estado = NULL;
	Conjunto_simbolos *conjunto_simbolos = NULL;

	printf("------------------------------------\n");

	estado = estado_create("ricardo", NORMAL);
	print_estado(estado);
	estado_destroy(estado);

	printf("------------------------------------\n");

	conjunto_simbolos = conjunto_simbolos_create("Cadeno");
	insert_simbolo(conjunto_simbolos, "hola");
	insert_simbolo(conjunto_simbolos, "ricardo");
	insert_simbolo(conjunto_simbolos, "funciona");
	insert_simbolo(conjunto_simbolos, "bien");

	printf("-----------Comparaciones --------\n");
	printf("%d\n", is_in_conjunto_simbolos(conjunto_simbolos, "ricardo"));
	printf("%d\n", is_in_conjunto_simbolos(conjunto_simbolos, "eoeoe"));

	printf("Num_elementos: %d\n", get_num_simbolos(conjunto_simbolos));
	print_conjunto_simbolos(conjunto_simbolos);
	conjunto_simbolos_destroy(conjunto_simbolos);

	printf("------------------------------------\n");

	return 0;

}