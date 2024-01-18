#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

///////////////////////// ESTRUCTURAS DE DATOS

struct celda {
    tipoelem info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIONES

/*Extraer la clave de una celda */
tipoclave _clave_elem(tipoelem *E) {
    return E->lexema; //se va a comparar por lexema
}


/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    return strcmp(cl1,cl2)==0 ? 0 : strcmp(cl1,cl2)>0 ? 1 : -1;
    //devuelve 0 si son iguales, num pos si la primera es mayor, num neg si la segunda es mayor
}


/////////////////////////// FIN PARTE MODIFICABLE
/////////////////////////////////////////////////////////////

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}


void destruir_arbol(abb *A) {
    if (*A != NULL) {
        destruir_arbol(&(*A)->izq);
        destruir_arbol(&(*A)->der);
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void leer(abb A, tipoelem *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, tipoelem E) {
    return _comparar_claves(cl, _clave_elem(&E));
}

char *mal(){
	return (char *) malloc(sizeof(char) * TAM);
}


//Función para buscar un nodo, si no lo encuentra, lo inserta
void buscar_nodo(abb *A, tipoclave cl, tipoelem *nodo) {
    if (es_vacio(*A)) {
        //no existe ese nodo en el arbol
        //se inserta
        *A = (abb) malloc(sizeof(struct celda));

        (*A)->info.lexema = (char *) malloc(sizeof(char) * TAM);

        strcpy((*A)->info.lexema, cl);

        (*A)->info.identificador = ID;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        nodo->identificador = ID;
        return;
    }
    int comp = _comparar_clave_elem(cl, (*A)->info);

    if (comp == 0) { // cl == A->info
        *nodo = (*A)->info; //se devuelve el nodo encontrado
    } else if (comp < 0) { // cl < A->info
        buscar_nodo(&(*A)->izq, cl, nodo);
    } else { // cl > A->info
        buscar_nodo(&(*A)->der, cl, nodo);
    }
}

void insertar_nodo(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info = E;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    } else {
        int comp = _comparar_clave_elem(_clave_elem(&E), (*A)->info);
        if (comp == 0) { // cl == A->info
            //no se inserta
        } else if (comp < 0) { // cl < A->info
            insertar_nodo(&(*A)->izq, E);
        } else { // cl > A->info
            insertar_nodo(&(*A)->der, E);
        }
    }
}


void imprimir_arbol(abb *A){
    if (*A != NULL) {
        imprimir_arbol(&(*A)->izq);
        imprimir_arbol(&(*A)->der);
        printf(" lex %s id %d\n", (*A)->info.lexema, (*A)->info.identificador);
    }
}
