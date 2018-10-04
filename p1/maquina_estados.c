/* ===================================================================
File: maquina_estados.c
Authors:Ricardo Riol, Francisco de Vicente Lana

Main de prueba
=================================================================== */
#include "estado.h"
#include <stdio.h>


int main(){
	Estado *estado = NULL;

	estado = estado_create("ricardo", NORMAL);
	print_estado(estado);
	estado_destroy(estado);
	return 0;

}