#include <stdio.h>
#include "definiciones.h"
#include "ts.h"
#include "abb.h"
#include <stdlib.h>
#include <string.h>

#define TAMM 8

abb arbol_simbolos;
componente_lex aux;

//función para meter las palabras reservadas al principio
void insertar(char *lex, int id){
    aux.identificador = id;
    aux.lexema = lex;
    insertar_nodo(&arbol_simbolos, aux);
}

//busca un elemento y devuelve su identificador
//Si no se encuentra en la tabla de símbolos, se inserta
int buscarElem(char *lexema){
    aux.identificador = 0;
    aux.lexema = NULL;
    buscar_nodo(&arbol_simbolos, lexema, &aux);
    return aux.identificador;
}

abb arbol_simbolos; //árbol que vamos a utilizar como tabla de símbolos

typedef componente_lex simbolo;

//palabras reservadas: palabras iniciales de la tabla de símbolos
simbolo palabras_reservadas[TAMM] = { {"int", INT}, {"import", IMPORT}, {"double", DOUBLE}, {"while", WHILE}, {"foreach", FOREACH}, {"return", RETURN}, {"void", VOID}, {"cast", CAST}};

//se crea el árbol y se insertan las palabras reservadas
void inicializar_ts(){
    crear(&arbol_simbolos);
    for(int i = 0; i < TAMM; i++){
        insertar(palabras_reservadas[i].lexema, palabras_reservadas[i].identificador);
    }
}

void imprimir(){
    imprimir_arbol(&arbol_simbolos);
}

//para destruir el árbol al terminar 
void destruir_ts(){
    free(aux.lexema);
    destruir_arbol(&arbol_simbolos);
}
