#ifndef SUTILS
#define SUTILS

const double EPS =  1.0e-6; /// EPS value for double comparison                                                                   \

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

#endif


