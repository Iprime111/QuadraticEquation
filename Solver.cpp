#include <cassert>
#include <math.h>
#include <cstdio>

#include "Solver.h"
#include "Logger.h"


int solve_equation (const double a, const double b, const double c, struct SOLUTION_RESULT *res){
    PushLog;
    solver_assert (!check_NaN_coefficients (a, b, c), number_is_nan, -1);
    solver_assert (!check_inf_coefficients (a, b, c), number_is_inf, -1);

    if (!compare_doubles (a, 0)){
        PopLog;
        return solve_linear (b, c, res);
    }

    PopLog;
    return solve_quadratic (a, b, c, res);
}

int solve_linear (const double b, const double c, struct SOLUTION_RESULT *res){
    PushLog;
    solver_assert (!check_NaN_coefficients (0.0, b, c), number_is_nan, -1);
    solver_assert (!check_inf_coefficients (0.0, b, c), number_is_inf, -1);

    if (compare_doubles (c, 0)){
        if (!compare_doubles (b, 0)){
            res->status = no_roots;

            PopLog;
            return 0;
        }

    }else if (!compare_doubles (b, 0)){
        res->status = inf_roots;

        PopLog;
        return 0;
    }

    res->status = one_root;
    res->answers[0] = -c / b;

    PopLog;
    return 0;
}

int solve_quadratic (const double a, const double b, const double c, struct SOLUTION_RESULT *res){
    PushLog;
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

    PopLog;
    return 0;
}

int check_NaN_coefficients (const double a, const double b, const double c){
   return (isnan (a) || isnan (b) || isnan (c) ? 1 : 0);
}

int check_inf_coefficients (const double a, const double b, const double c){
    return (isinf (a) || isinf (b) || isinf (c) ? 1 : 0);
}

enum COMPARE_RESULT compare_doubles (const double a, const double b){
    PushLog;
    if (a - b > EPS){
        PopLog;
        return GREATER;
    }else if (b - a > EPS){
        PopLog;
        return LESS;
    }else{
        PopLog;
        return EQUAL;
    }
    PopLog;
}
