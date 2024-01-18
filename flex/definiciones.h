#ifndef DEFINICIONES_H
#define DEFINICIONES_H

typedef struct {
    char *lexema;
    int identificador;
} componente_lex;

#define TAM 40

//palabras reservadas
#define IMPORT 300
#define ID 301
#define DOUBLE 302
#define INT 303
#define WHILE 304
#define FOREACH 305
#define RETURN 306
#define VOID 307
#define CAST 308

//fin de fichero
#define ENDOFF 309

//tokens
#define PUNTO 312
#define COMA 318
#define PUNTOYCOMA 313
#define PARENTESISIZQ 314
#define PARENTESISDER 315
#define CORCHETEIZQ 316
#define CORCHETEDER 317
#define LLAVEIZQ 319
#define LLAVEDER 320

//
#define CADENA 323
#define NUMERO 324

//OPERADORES
#define COMPARACION 310 //con igual
#define ASIGNACION 311
#define MENORQUE 325
#define MENOROIGUAL 326
#define MAYORQUE 327
#define MAYOROIGUAL 328
#define INCREMENTO 329
#define MASIGUAL 330
#define SUMA 331
#define DECREMENTO 332
#define MENOSIGUAL 333
#define RESTA 334
#define PORIGUAL 335
#define MULTIPLICACION 336
#define ENTREIGUAL 337
#define DIVISION 338


#define ERROR1 400
#define ERROR2 401



#endif
