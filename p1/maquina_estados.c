/* ===================================================================
File: maquina_estados.c
Authors: Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include <stdio.h>
#include "estado.h"
#include "conjunto_simbolos.h"
#include "transicion.h"



int main() {
	Estado *estado1 = NULL;
	Estado *estado2 = NULL;
	Conjunto_simbolos *conjunto_simbolos = NULL;
	Transicion *transicion = NULL;

	printf("---------------EASTADO---------------------\n");

	estado1 = estado_create("ricardo", NORMAL);
	print_estado(estado1);

	estado2= estado_create("Paco", FINAL);
	print_estado(estado2);

	printf("--------------CONJUNTOS DE SIMBOLOS---------------------\n");

	conjunto_simbolos = conjunto_simbolos_create("A");
	insert_simbolo(conjunto_simbolos, "a");
	insert_simbolo(conjunto_simbolos, "b");
	insert_simbolo(conjunto_simbolos, "c");
	insert_simbolo(conjunto_simbolos, "d");

	printf("-----------Comparaciones --------\n");
	printf("%d\n", is_in_conjunto_simbolos(conjunto_simbolos, "a"));
	printf("%d\n", is_in_conjunto_simbolos(conjunto_simbolos, "f"));

	printf("Num_elementos: %d\n", get_num_simbolos(conjunto_simbolos));
	print_conjunto_simbolos(conjunto_simbolos);


	printf("-------------------TRANSICIONES-----------------\n");
	transicion = transicion_create(estado1, estado2, "a");
	transicion_print(transicion);



	conjunto_simbolos_destroy(conjunto_simbolos);
	estado_destroy(estado1);
	estado_destroy(estado2);
	transicion_destroy(transicion);
	return 0;

}