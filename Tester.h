#ifndef TESTER
#define TESTER

#include <cstdio>
#include <math.h>
#include "SolverUtils.h"

/*!
    @brief Clears file input buffer
    @param[in] file File pointer
    @return Status of an input operation
    Clears input buffer and searches for EOF symbol
*/
enum INPUT_STATUS clear_file_buf (FILE *file);

/*!
    @brief Reads test data chunk
    @param[in] fp File pointer
    @param[out] answer Right answer structure pointer
    @param[out] a,b,c Coefficients pointers
    @return Status of an input operation
    Reads line from test file and writes test data into given variables
*/
enum INPUT_STATUS read_data_chunk (FILE *fp, struct SOLUTION_RESULT *answer, double *a, double *b, double *c);

/*!
    @brief Shows message about wrong-passed test
    @param[in] test_number Current test number
    @param[in] right_answer Right answer readed from file
    @param[in] answer Answer given by program
    @param[in] a,b,c Equation coefficients
    @return 0 if successful, -1 if not
    Shows message with data about wrong-passed test number, right and wrong answer and equation coefficients
*/
int show_error (int test_number, const struct SOLUTION_RESULT *right_answer, const struct SOLUTION_RESULT *answer, double a, double b, double c);

/*!
    @brief Shows message about successfully passed test
    @param[in] test_number Number of current test
    @return Nothing
    Shows message with data about passed test number
*/
void show_success (int test_number);

/*!
    @brief Shows all test results
    @param[in] right_answers Number of right answers
    @param[in] answers Number of answers
    @return Nothing
    Shows quantity of all tests and passed tests
*/
void show_test_results (int right_answers, int answers);

/*!
    @brief Prints roots of the equation and it's solution status
    @param[in] answer Roots and status structure
    @return Nothing
    Prints roots of the equation and it's solution status in form of <status in decimal format> <root one (if exists)> <root two (if exists)>
*/
void print_roots (const struct SOLUTION_RESULT *answer);

/*!
    @brief Does unit tests of solve_equation function
    @param[in] filename Path to test file
    @return 0 if succesful, -1 if not
    Reads data from test file, pushes it to solve_equation function and compares results with right answers
*/
int Test (char *filename);

/*!
    @brief Compares two answers
    @param[in] res1 First answer
    @param[in] res2 Second answer
    @return true if results are equal, false if not
    Compares solution status and all existing roots of two given solutions
*/
bool are_results_equal (struct SOLUTION_RESULT *res1, struct SOLUTION_RESULT *res2);

/*!
    @brief Tests one chunk of data
    @param[in]  r_answer Right answer
    @param[in] answer Given answer
    @param[in] a,b,c Equation coefficients
*/
bool Test_one_chunk (struct SOLUTION_RESULT *r_answer, struct SOLUTION_RESULT *answer, double a, double b, double c);
#endif
