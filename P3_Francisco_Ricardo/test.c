/* ===================================================================
File: test1.c
Authors: Ricardo Riol gonzalez, Francisco de Vicente Lana

Test para ir probando "sobre la marcha"
=================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

int main(int argc, char **argv)
{
    /* DECLARACIÓN DE UN PUNTERO A UN AFND */
    AFND *p_afnd0, *p_afnd1, *suma, *vacio;

    vacio = AFND1ODeSimbolo(NULL);

    AFNDImprime(stdout, vacio);

    /* Definicion afnd que reconoce el 0 */
    p_afnd0 = AFND1ODeSimbolo("0");

    AFNDImprime(stdout, p_afnd0);

    /* Definicion afnd que reconoce el 1 */
    p_afnd1 = AFND1ODeSimbolo("1");

    AFNDImprime(stdout, p_afnd1);

    /* Suma de ambos */
    suma = AFND1OUne(p_afnd0, p_afnd1);
    AFNDImprime(stdout, suma);


    /* SE LIBERAN TODOS LOS RECURSOS ASOCIADOS CON EL AFND */
    AFNDElimina(p_afnd0);
    AFNDElimina(p_afnd1);
    AFNDElimina(suma);
    AFNDElimina(vacio);


    return EXIT_SUCCESS;
}