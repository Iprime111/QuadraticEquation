#include "Solver.h"
#include <cassert>
#include <math.h>

//TODO test
/*test(...) {
 - read data from file
 - calls solver
 - check answer of solver with given data
}*/

struct solution_result *solve_equation(const double a, const double b, const double c){
    assert(!check_NaN_coefficients(a, b, c));
    assert(!check_inf_coefficients(a, b, c));

    if(!compare_doubles(a, 0)) return solve_linear(a, b);

    return solve_quadratic(a, b, c);
}

struct solution_result *solve_linear(const double b, const double c){

    struct solution_result *res = NULL;

    assert((void("Entered coefficient values are not forming the equation!"), compare_doubles(b, 0))); // TODO b == 0 case

    res = (struct solution_result *)calloc(1, SOL_SIZE(1));
    res->status = one_root;
    res->answers[0] = -c / b;

    return res;
}

struct solution_result *solve_quadratic(const double a, const double b, const double c){
// TODO asserts on inf, nan

    struct solution_result *res = NULL;
    double d = b * b - 4 * a * c;

    if(compare_doubles(d, 0) == 1){
        res = (struct solution_result *)calloc(1, SOL_SIZE(2));
        res->status = two_roots;
        double sqroot = sqrt(d);
        res->answers[0] = (-b + sqroot) / (2 * a);
        res->answers[1] = (-b - sqroot) / (2 * a);
    }else if(compare_doubles(d, 0) == -1){
        res = (struct solution_result *)calloc(1, SOL_SIZE(0));
        res->status = no_roots;
    }else{
        res = (struct solution_result *)calloc(1, SOL_SIZE(1));
        res->status = one_root;
        res->answers[0] = -b / (2 * a);
    }
    return res;
}

int check_NaN_coefficients(const double a, const double b, const double c){
   return (isnan(a) || isnan(b) || isnan(c) ? 1 : 0);
}

int check_inf_coefficients(const double a, const double b, const double c){
    return (isinf(a) || isinf(b) || isinf(c) ? 1 : 0);
}

int compare_doubles(const double a, const double b){
    if(a - b > EPS){
        return 1;
    }else if(b - a > EPS){
        return -1;
    }else{
        return 0;
    }
}
