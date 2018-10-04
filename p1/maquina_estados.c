/* ===================================================================
File: maquina_estados.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include "estado.h"
#include "alfabeto.h"
#include <stdio.h>


int main(){
	Estado *estado = NULL;
	Alfabeto *alfabeto = NULL;

	printf("------------------------------------\n");

	estado = estado_create("ricardo", NORMAL);
	print_estado(estado);
	estado_destroy(estado);

	printf("------------------------------------\n");

	alfabeto = alfabeto_create();
	insertar_simbolo(alfabeto, "hola");
	insertar_simbolo(alfabeto, "ricardo");
	insertar_simbolo(alfabeto, "funciona");
	insertar_simbolo(alfabeto, "bien");

	printf("Num_elementos: %d\n", get_num_simbolos(alfabeto));
	print_alfabeto(alfabeto);
	alfabeto_destroy(alfabeto);

	return 0;

}