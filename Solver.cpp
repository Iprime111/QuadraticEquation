#include <cassert>
#include <math.h>
#include <cstdio>

#include "Solver.h"
#include "Logger.h"


int solve_equation (const double a, const double b, const double c, struct SOLUTION_RESULT *res){
    PushLog(2);
    solver_assert (!check_NaN_coefficients (a, b, c), number_is_nan, -1);
    solver_assert (!check_inf_coefficients (a, b, c), number_is_inf, -1);

    if (!compare_doubles (a, 0)){
        RETURN(solve_linear (b, c, res));
    }

    RETURN(solve_quadratic (a, b, c, res));
}

int solve_linear (const double b, const double c, struct SOLUTION_RESULT *res){
    PushLog(3);
    solver_assert (!check_NaN_coefficients (0.0, b, c), number_is_nan, -1);
    solver_assert (!check_inf_coefficients (0.0, b, c), number_is_inf, -1);

    if (compare_doubles (c, 0)){
        if (!compare_doubles (b, 0)){
            res->status = no_roots;

            RETURN(0);
        }

    }else if (!compare_doubles (b, 0)){
        res->status = inf_roots;

        RETURN(0);
    }

    res->status = one_root;
    res->answers[0] = -c / b;

    RETURN(0);
}

int solve_quadratic (const double a, const double b, const double c, struct SOLUTION_RESULT *res){
    PushLog(3);
    solver_assert (!check_NaN_coefficients (a, b, c), number_is_nan, -1);
    solver_assert (!check_inf_coefficients (a, b, c), number_is_inf, -1);

    double d = b * b - 4 * a * c;

    if (compare_doubles (d, 0) == GREATER){
        res->status = two_roots;
        double sqroot = sqrt (d);
        res->answers[0] = (-b + sqroot) /  (2 * a);
        res->answers[1] = (-b - sqroot) /  (2 * a);
    }else if (compare_doubles (d, 0) == LESS){
        res->status = no_roots;
    }else{
        res->status = one_root;
        res->answers[0] = -b / (2 * a);
    }

    RETURN(0);
}

int check_NaN_coefficients (const double a, const double b, const double c){
    PushLog(4);
    RETURN((isnan (a) || isnan (b) || isnan (c) ? 1 : 0));
}

int check_inf_coefficients (const double a, const double b, const double c){
    PushLog(4);
    RETURN((isinf (a) || isinf (b) || isinf (c) ? 1 : 0));
}

enum COMPARE_RESULT compare_doubles (const double a, const double b){
    PushLog(4);
    if (a - b > EPS){
        RETURN(GREATER);
    }else if (b - a > EPS){
        RETURN(LESS);
    }else{
        RETURN(EQUAL);
    }
}
