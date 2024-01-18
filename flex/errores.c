#include <stdlib.h>
#include <stdio.h>
#include "definiciones.h"

void errores(int n) {
    switch (n) {
        case ERROR1:
            printf("Error: lexema demasiado largo\n");
            break;
        case ERROR2:
            printf("Error: símbolo no reconocido\n");
            break;
    }
}