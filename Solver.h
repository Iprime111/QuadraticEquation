#ifndef SOLVER
#define SOLVER

#include "SolverUtils.h"


/*!
    Compares two doubles a and b
    \param a First double
    \param b Second double
    \return 1 if a is bigger than b, -1 if b is bigger than a and 0 if they are equal
*/
int compare_doubles(const double a, const double b);

/*!
    Solves a*x^2 + b*x + c = 0 equation with given coefficients
    \param a,b,c Equation coefficients
    \return Struct that contains equation roots and solution result status
*/
struct solution_result *solve_equation(const double a, const double b, const double c);

/*!
    Solves linear equation with given coefficients b and c
    \param b,c Equation coefficients
    \return Struct that contains equation roots and solution result status
*/
struct solution_result *solve_linear(const double b, const double c);

/*!
    Solves quadratic equation with given coefficients a, b and c
    \param a,b,c Equation coefficients
    \return Struct that contains equation roots and solution result status
*/
struct solution_result *solve_quadratic(const double a, const double b, const double c);

/*!
    Checks if some of equation coefficients have NaN value
    \param a,b,c Equation coefficients
    \return Check result
*/
int check_NaN_coefficients(const double a, const double b, const double c);

/*!
    Checks if some of equation coefficients have inf value
    \param a,b,c Equation coefficients
    \return Check result
*/
int check_inf_coefficients(const double a, const double b, const double c);

#endif


