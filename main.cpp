#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Logger.h"
#include "Solver.h"
#include "IOFunctions.h"
#include "SolverUtils.h"
#include "Tester.h"

#include <assert.h>

int main (int argc, char *argv[]){
    open_log();

    AddLog;
    solver_assert (argc < 3, too_many_arguments, 0);

    if (argc > 1){
        Test (argv[1]);

        PopLog;
        return 0;
    }

    double a = NAN, b = NAN, c = NAN;

    enum INPUT_STATUS input_res = request_input (&a, &b, &c);
    solver_assert (input_res != exit_status, exit_status_found, 0);

    struct SOLUTION_RESULT result = {no_result, {NAN, NAN}};
    solve_equation (a, b, c, &result);

    if (result.status != no_result){
        show_results (&result);
    }

    PopLog;
    atexit(close_log);

    return 0;
}
