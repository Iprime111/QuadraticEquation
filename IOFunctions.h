#ifndef IOFUNC
#define IOFUNC

#include "SolverUtils.h"

/*!
    Clears input buffer and searches for 'q' symbol to quit
    \return Status of input operation
*/
enum input_status clear_buffer();

/*!
    Reads coefficient values from console
    \param a,b,c Pointers to read values
    \return Status of an input operation
*/
enum input_status get_input(double *a, double *b, double *c);

/*!
    Shows console user interface and scans all equation coefficients
    \param a,b,c Pointers to read values
    \return Status of an input operation
*/
enum input_status request_input(double *a, double *b, double *c);

/*!
    Prints solution result in console
    \param result Struct that contains equation roots and solution result status
    \return Nothing
*/
void show_results(const struct solution_result *result);

#endif



