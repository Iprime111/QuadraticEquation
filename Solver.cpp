#include "Solver.h"
#include <cassert>
#include <math.h>
#include <cstdio>


int solve_equation(const double a, const double b, const double c, struct solution_result *res){
    solver_assert(!check_NaN_coefficients(a, b, c), number_is_nan, -1);
    solver_assert(!check_inf_coefficients(a, b, c), number_is_inf, -1);

    if(!compare_doubles(a, 0)) return solve_linear(b, c, res);

    return solve_quadratic(a, b, c, res);
}

int solve_linear(const double b, const double c, struct solution_result *res){
    solver_assert(!check_NaN_coefficients(0.0, b, c), number_is_nan, -1);
    solver_assert(!check_inf_coefficients(0.0, b, c), number_is_inf, -1);

    if(compare_doubles(c, 0)){
        if(!compare_doubles(b, 0)){
            res->status = no_roots;
            solver_assert(0, not_an_equation, -1);
        }

    }else if(!compare_doubles(b, 0)){
        res->status = inf_roots;
        return 0;
    }

    res->status = one_root;
    res->answers[0] = -c / b;

    return 0;
}

int solve_quadratic(const double a, const double b, const double c, struct solution_result *res){
    solver_assert(!check_NaN_coefficients(a, b, c), number_is_nan, -1);
    solver_assert(!check_inf_coefficients(a, b, c), number_is_inf, -1);

    double d = b * b - 4 * a * c;

    if(compare_doubles(d, 0) == GREATER){
        res->status = two_roots;
        double sqroot = sqrt(d);
        res->answers[0] = (-b + sqroot) / (2 * a);
        res->answers[1] = (-b - sqroot) / (2 * a);
    }else if(compare_doubles(d, 0) == LESS){
        res->status = no_roots;
    }else{
        res->status = one_root;
        res->answers[0] = -b / (2 * a);
    }
    return 0;
}

int check_NaN_coefficients(const double a, const double b, const double c){
   return (isnan(a) || isnan(b) || isnan(c) ? 1 : 0);
}

int check_inf_coefficients(const double a, const double b, const double c){
    return (isinf(a) || isinf(b) || isinf(c) ? 1 : 0);
}

int compare_doubles(const double a, const double b){
    if(a - b > EPS){
        return GREATER;
    }else if(b - a > EPS){
        return LESS;
    }else{
        return EQUAL;
    }
}
