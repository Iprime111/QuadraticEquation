#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Solver.h"
#include "IOFunctions.h"
#include "SolverUtils.h"

int main(void){


    double a = NAN, b = NAN, c = NAN;

    enum input_status input_res = request_input(&a, &b, &c);
    solver_assert(input_res != exit_status, exit_status_found, 0);

    struct solution_result *result = solve_equation(a, b, c);

    if(result != NULL){
        show_results(result);
        free(result);
    }
    return 0;
}
