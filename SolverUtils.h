#ifndef SUTILS
#define SUTILS

const double EPS =  1.0e-6;
#define SOL_SIZE(X) (sizeof(struct solution_result) + X * sizeof(double))
#define solver_assert(EXP,CODE,RET) if(!(EXP)){assert_manager(CODE, #EXP); return RET;}

enum solution_status {
    no_roots    = 0,
    one_root    = 1,
    two_roots   = 2,
    inf_roots   = 3
};
enum input_status {
    ok_status       = 0,
    wrong_format    = 1,
    exit_status     = -1
};

enum error_code{
    not_an_equation     = 0,
    number_is_nan       = 1,
    number_is_inf       = 2,
    not_enough_pointers = 3,
    eof_found           = 4,
    pointer_is_null     = 5,
    exit_status_found   = 6
};

struct solution_result{
    enum solution_status status;
    double answers[];
};

/*!
    Shows error in console
    \param code error code
    \return Nothing
*/
void assert_manager(enum error_code code, char *expr);

#endif


