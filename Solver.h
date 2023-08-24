#ifndef SOLVER
#define SOLVER

#include "SolverUtils.h"

/*!
    @brief Compares two doubles a and b
    @param[in] a First double
    @param[in] b Second double
    @return GREATER if a is bigger than b, LESS if b is bigger than a and EQUAL if they are equal
    Function that compares two doubles and returns COMPARE_RESULT enum
*/
enum COMPARE_RESULT compare_doubles (const double a, const double b);

/*!
    @brief Solves given equation
    @param[in] a,b,c Equation coefficients
    @return Struct that contains equation roots and solution result status
    Solves a*x^2 + b*x + c = 0 equation with given coefficients
*/
int solve_equation (const double a, const double b, const double c, struct SOLUTION_RESULT *res);

/*!
    @brief Solves given linear equation
    @param[in] b,c Equation coefficients
    \param[out] res Output result structure
    \return 0 if succesful, -1 if not
    Solves linear equation with given coefficients b and c
*/
int solve_linear (const double b, const double c, struct SOLUTION_RESULT *res);

/*!
    @brief Solves given quadratic equation
    @param[in] a,b,c Equation coefficients
    @param[out] res Output result structure
    @return 0 if succesful, -1 if not
    Solves quadratic equation with given coefficients a, b and c (a != 0)
*/
int solve_quadratic (const double a, const double b, const double c, struct SOLUTION_RESULT *res);

/*!
    @brief Checks if some of equation coefficients have NaN value
    @param[in] a,b,c Equation coefficients
    @return 1 if at least one of coefficients has NaN value and 0 if not
*/
int check_NaN_coefficients (const double a, const double b, const double c);

/*!
    @brief Checks if some of equation coefficients have inf value
    @param[in] a,b,c Equation coefficients
    @return 1 if at least one of coefficients has inf value and 0 if not
*/
int check_inf_coefficients (const double a, const double b, const double c);

#endif


