#ifndef SOLVER_ASSERT
#define SOLVER_ASSERT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#include "ColorConsole.h"
#include "Logger.h"

const int MAX_LINE_LENGTH = 300;

/*! @brief Custom assert implementation that provides information about file, function and line, do not stops the program and do not calls PopLog()*/
#define solver_assert_without_logger(EXP, CODE, RET) \
    solver_assert_internal(EXP, CODE, RET, {})

/*! @brief Custom assert implementation that provides information about file, function and line and do not stops the program*/
#define solver_assert(EXP, CODE, RET) \
    solver_assert_internal(EXP, CODE, RET, PopLog())

/*! @brief Custom assert implementation that provides information about file, function and line, do not stops the program and running the CALLBACK expression*/
#define solver_assert_internal(EXP, CODE, RET, CALLBACK)                                                           \
            do{                                                                                 \
                if (!(EXP)){                                                                    \
                    assert_perror_solver (CODE, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                    CALLBACK;                                                                   \
                    return RET;                                                                 \
                }                                                                               \
            }while(0)

/// @brief Code of detected error
enum ERROR_CODE{
    not_an_equation     = 0,  ///< Processed expression is not an equation
    number_is_nan       = 1,  ///< Given number has NaN value
    number_is_inf       = 2,  ///< Given numver has inf value
    not_enough_pointers = 3,  ///< One or multiple pointers have one address
    eof_found           = 4,  ///< EOF symbol has been found in input buffer
    pointer_is_null     = 5,  ///< Given pointer has NULL value
    exit_status_found   = 6,  ///< One ore multiple functions have returned exit_status
    cannot_open_file    = 7,  ///< Error is occuried while opening file
    wrong_data_format   = 8,  ///< File data have wrong format
    too_many_arguments  = 9,  ///< Too many console line arguments have been passed
    file_close_error    = 10, ///< Error is occuried while closing file
    length_too_big      = 11  ///< String length is too big
};

/*!
    @brief Shows error in console
    @param[in] code Error code
    @param[in] expr Tested expression
    @return Nothing
    Shows detailed error description, it's file and line and tested expression
*/
void assert_perror_solver (enum ERROR_CODE code, const char *source_path, const char *function, unsigned int line);

char *read_source (const char *source_filename, unsigned int line, unsigned int *line_shift);

FILE *open_file (const char *filename);

char *get_binary_file_path ();

time_t get_last_modified_date (const char *filename);

bool should_read_source (const char *source_filename);

bool read_non_empty_string (char *str, FILE *fp, bool *read_next_line);

#endif