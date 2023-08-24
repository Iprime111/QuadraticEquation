#ifndef SUTILS
#define SUTILS

const double EPS =  1.0e-6;/// EPS value for double comparison

/*! @brief Custom assert implementation that provides information about file, function and line and do not stops the program*/
#define solver_assert(EXP, CODE, RET)                                                           \
            do{                                                                                 \
                if (!(EXP)){                                                                    \
                    assert_perror_solver (CODE, #EXP, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                    PopLog;                                                                    \
                    return RET;                                                                 \
                }                                                                               \
            }while(0)                                                                           \

/// @brief Current solution staus
enum SOLUTION_STATUS {
    no_roots    = 0, ///< Equation has no roots
    one_root    = 1, ///< Equation has one root
    two_roots   = 2, ///< Equation has two roots
    inf_roots   = 3, ///< Equation has infinitely many roots
    no_result   = 4  ///< Equation hasn't been solved yet
};

/// @brief Status of current input operation
enum INPUT_STATUS {
    ok_status       = 0, ///< input operation worked as expected
    wrong_format    = 1, ///< input data have wrong format
    exit_status     = -1 ///< EOF or quit symbol has been found in input buffer
};

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

/// @brief Doubles comparison result
enum COMPARE_RESULT{
    GREATER     = 1,    ///< First argument is greater than second
    LESS        = -1,   ///< First argument is less than second
    EQUAL       = 0     ///< Arguments are equal
};

/// @brief Struct that contains roots of equation and it's solution status
struct SOLUTION_RESULT{
    enum SOLUTION_STATUS status; ///< Status of current solution
    double answers[2]; ///< Roots of the equation
};

/*!
    @brief Shows error in console
    @param[in] code Error code
    @param[in] expr Tested expression
    @return Nothing
    Shows detailed error description, it's file and line and tested expression
*/
void assert_perror_solver (enum ERROR_CODE code, char *expr, const char *file, const char *function, int line);

#endif


