#include "SolverUtils.h"
#include <cstdio>

void assert_manager(enum error_code code, char *expr){
    switch(code){
        case not_an_equation:
            printf("Folowing expression is not an equation!");
            break;
        case number_is_nan:
            printf("Requested number is NaN!");
            break;
        case number_is_inf:
            printf("Requested number is inf!");
            break;
        case not_enough_pointers:
            printf("One or multiple pointers are similar!");
            break;
        case eof_found:
            printf("EOF symbol has been found in input buffer!");
            break;
        case pointer_is_null:
            printf("Requested pointer is NULL!");
            break;
        case exit_status_found:
            printf("Exit status found!");
            break;
        default:
            printf("Unknown error!");
    }
    printf(" (%s)\n", expr);
}
