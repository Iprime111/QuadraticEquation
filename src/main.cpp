#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Logger.h"
#include "Solver.h"
#include "IOFunctions.h"
#include "SolverUtils.h"
#include "Tester.h"

int main (int argc, char *argv[]){

    PushLog(1);
    solver_assert (argc < 3, too_many_arguments, 0);

    if (argc > 1){
        Test (argv[1]);

        RETURN 0;
    }

    double a = NAN, b = NAN, c = NAN;

    enum INPUT_STATUS input_res = request_input (&a, &b, &c);
    solver_assert (input_res != eof_status, eof_found, 0);

    if (input_res == exit_status)
        return 0;

    struct SOLUTION_RESULT result = {no_result, {NAN, NAN}};
    solve_equation (a, b, c, &result);

    if (result.status != no_result){
        show_results (&result);
    }

    RETURN 0;
}
