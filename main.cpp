#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Solver.h"
#include "IOFunctions.h"
#include "SolverUtils.h"

int main(void){


    double a = NAN, b = NAN, c = NAN;

    show_interface(&a, &b, &c);

    struct solution_result *result = solve_equation(a, b, c);

    if(result != NULL){
        show_results(result);
        free(result);
    }
    return 0;
}
