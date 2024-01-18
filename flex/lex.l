/*SECCIÓN DEFINICIONES*/

%{

#include "definiciones.h"
#include "errores.h"
#include "abb.h"
#include "ts.h"

%}

/*Indica a flex que lea sólo un fichero de entrada*/
%option noyywrap
/*Permite obtener el número de línea*/
%option yylineno

/*Indica a flex que no necesitamos generar la función yyunput*/
%option nounput

/*TOKENS*/
LETRA [a-zA-Z]
CERO 0
DIGITO_NOCERO [1-9]
CARACTER .
C [^\/\*]
ESPACIO [" "]
SALTO_LINEA [\n]
TAB ["\t"]
GUION ["_"]
PUNTO_ ["."]
COMA_ ","
PUNTOCOMA ";"
DOSPUNTOS_ ":"
PAR_IZQ "("
PAR_DER ")"
CORCH_IZQ "["
CORCH_DER "]"
LLAVE_IZQ "{"
LLAVE_DER "}"

START_EXPONENTE_DEC ([eE][+-]?)


ALFANUM ({LETRA}|{GUION})({LETRA}|{DIGITO_NOCERO}|{CERO}|{GUION})*
NUM_ENTERO_DEC {CERO}|{DIGITO_NOCERO}({DIGITO_NOCERO}|{CERO}|{GUION})*
NUM_FLOAT_DEC ({NUM_ENTERO_DEC}{PUNTO_}{NUM_ENTERO_DEC}{START_EXPONENTE_DEC}?)
STRING \"{CARACTER}*\"

CHAR_ESCP \\.


COMENTARIO_LIN \/\/({CHAR_ESCP}|{C})*{SALTO_LINEA}

INI_C "/*"
FIN_C "*/"
COMENTARIO_BLOQ {INI_C}({CHAR_ESCP}|{C}|{SALTO_LINEA}|\*)*{FIN_C}


COMPARACION_ "=="
MENORIGUAL_ "<="
MAYORIGUAL_ ">="
MASMAS "++"
MASIGUAL_ "+="
MENOSMENOS "--"
MENOSIGUAL_ "-="
PORIGUAL_ "*="
DIVIGUAL "/="
IGUAL "="
MENOR "<"
MAYOR ">"
MAS "+"
MENOS "-"
MULT "*"
DIV "/"



/*REGLAS*/
%%
{ALFANUM} {return buscarElem(yytext);}
{NUM_ENTERO_DEC} {return NUMERO;}
{NUM_FLOAT_DEC} {return NUMERO;}
{STRING} {return CADENA;}
{COMPARACION_} {return COMPARACION;}
{IGUAL} {return ASIGNACION;}
{MENOR} {return MENORQUE;}
{MENORIGUAL_} {return MENOROIGUAL;}
{MAYOR} {return MAYORQUE;}
{MAYORIGUAL_} {return MAYOROIGUAL;}
{MASMAS} {return INCREMENTO;}
{MASIGUAL_} {return MASIGUAL;}
{MENOSMENOS} {return DECREMENTO;}
{MENOSIGUAL_} {return MENOSIGUAL;}
{PORIGUAL_} {return PORIGUAL;}
{DIVIGUAL} {return ENTREIGUAL;}
{MAS} {return SUMA;}
{MENOS} {return RESTA;}
{MULT} {return MULTIPLICACION;}

{PUNTO_} {return PUNTO;}
{PUNTOCOMA} {return PUNTOYCOMA;}
{PAR_IZQ} {return PARENTESISIZQ;}
{PAR_DER} {return PARENTESISDER;}
{CORCH_IZQ} {return CORCHETEIZQ;}
{CORCH_DER} {return CORCHETEDER;}
{LLAVE_IZQ} {return LLAVEIZQ;}
{LLAVE_DER} {return LLAVEDER;}
{COMA_} {return COMA;}

{COMENTARIO_LIN} /*ignora el comentario de línea*/
{COMENTARIO_BLOQ} 

"/+"	{register int c;
	register int contador = 1;
	while (contador > 0){
		c = input();
		if (c == '/'){
			c = input();
			if (c == '+'){
				contador++;/*se abrio un nuevo comentario*/
			}
		} else if (c == '+'){
			c = input();
			if (c == '/'){
				contador--; /*se cerro un comentario*/
			}
		}
		
	}
	}	

{DIV} {return DIVISION;}

{SALTO_LINEA}
{ESPACIO}
{TAB}

<<EOF>> {return ENDOFF;}
	errores(ERROR2); /*Si el caracter encontrado no coincide con ninguno de los anteriores*/

%%


/*CÓDIGO DE USUARIO*/
int abrir_archivo()
{
    yyin = fopen("regression.d", "r");
    if (yyin == NULL){
        return 0;
    }
    return 1;
}



void cerrar_archivo()
{
    fclose(yyin);
    yylex_destroy();
    printf("Archivo cerrado correctamente\n");
}


void sig_comp_lex(componente_lex *componente){
    componente->identificador = yylex();
    strcpy(componente->lexema, yytext);
    
    //printf("comp lex %s\n", componente->lexema);
}


