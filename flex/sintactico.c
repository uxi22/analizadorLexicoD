#include <stdio.h>
#include "definiciones.h"
#include <stdlib.h>
#include "lex.yy.h"


void ejecutar(){
	//se crea el componente léxico y se reserva memoria para el lexema
    componente_lex componente;
    componente.lexema = (char *) malloc(sizeof(char) * (TAM));
    sig_comp_lex(&componente); //le pide el siguiente componente léxico al analizador léxico
    while (componente.identificador != ENDOFF) {
        printf("<%d, \"%s\"> \n", componente.identificador, componente.lexema);
        sig_comp_lex(&componente);
        //pide siguiente componente léxico
    }
    printf("<%d, \"%s\">\n", componente.identificador, componente.lexema); //último, el end of file
    componente.identificador = 0;
    //componente.lexema = NULL;
    free(componente.lexema);
}
