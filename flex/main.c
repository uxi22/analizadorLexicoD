#include <stdio.h>
#include <stdlib.h>
#include "ts.h"
#include "sintactico.h"
#include "lex.yy.h"


int main() {
    inicializar_ts(); //se inicializa la tabla de símbolos
    if (abrir_archivo() == 0){
    	printf("error abriendo el archivo\n");
    	return EXIT_FAILURE;
    }
	printf("archivo abierto\n");
    imprimir();
    ejecutar(); //del analizador sintáctico
    //una vez que se termina de ejecutar, se destruye la tabla de símbolos
    printf("Fin de ejecución\n");
    imprimir();
    destruir_ts();
    printf("tabla de simbolos destruida\n");
    cerrar_archivo();
    exit(EXIT_SUCCESS);
}
