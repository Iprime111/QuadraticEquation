#ifndef IOFUNC
#define IOFUNC

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "Logger.h"
#include "SolverAssert.h"
#include "SolverUtils.h"

/*!
    @brief Buffer clear function
    @return Status of an input operation
    Clears input buffer and searches for 'q' symbol to quit
*/
enum INPUT_STATUS clear_buffer ();

/*!
    @brief Reads coefficient values from console
    @param[out] a,b,c Pointers to read values
    @return Status of an input operation
    Reads coefficient values with all checks and buffer clear
*/
enum INPUT_STATUS get_input (double *a, double *b, double *c);

/*!
    @brief Requests data from user
    @param[out] a,b,c Pointers to read values
    @return Status of an input operation
    Shows console user interface and scans all equation coefficients
*/
enum INPUT_STATUS request_input (double *a, double *b, double *c);

/*!
    @brief Prints solution result in console
    @param result Struct that contains equation roots and solution result status
    @return Nothing
    Prints solution status and all of the equation roots in console
*/
void show_results (const struct SOLUTION_RESULT *result);

#endif



