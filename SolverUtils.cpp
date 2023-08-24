#include <cstdio>

#include "SolverUtils.h"
#include "ColorConsole.h"
#include "Logger.h"

void assert_perror_solver (enum ERROR_CODE code, char *expr, const char *file, const char* function, int line){

    const char* msg = "??? Unknown code ???";

    #define MSG_(err_code, descr)       \
        case err_code:                  \
            msg = #err_code ": " descr; \
            break;

    switch (code) {
        MSG_ (not_an_equation,      "Folowing expression is not an equation!")
        MSG_ (number_is_nan,        "Requested number is NaN!")
        MSG_ (number_is_inf,        "Requested number is inf!")
        MSG_ (not_enough_pointers,  "One or multiple pointers are similar!")
        MSG_ (eof_found,            "EOF symbol has been found in input buffer!")
        MSG_ (pointer_is_null,      "Requested pointer is NULL!")
        MSG_ (exit_status_found,    "Exit status found!")
        MSG_ (cannot_open_file,     "Can not open file for reading!")
        MSG_ (wrong_data_format,    "Incorrect file data format!")
        MSG_ (too_many_arguments,   "Too many command line arguments!")
        MSG_ (file_close_error,     "Can not close file!")
        MSG_ (length_too_big,       "String length is too big!")

        default:
            msg = "Unknown error!";
            break;
    }

    printf_color (Console_red, Console_normal, "%s  ", msg);


    #ifdef _DEBUG
        printf_color (Console_red, Console_normal, "(%s in file: %s:%d function: %s)\n",\
                     expr, file, line, function);
        #ifdef _SHOW_STACK_TRACE
            printf_color (Console_red, Console_bold, "STACK TRACE:\n");

            Show_stack_trace ();
        #else
            printf ("\n");
        #endif
    #endif

    #undef MSG_
}
