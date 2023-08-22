#ifndef SUTILS
#define SUTILS

const double EPS =  1.0e-6;
#define SOL_SIZE(X) (sizeof(struct solution_result) + X * sizeof(double))
#define solver_assert(EXP, CODE, RET) (assert_manager(); return)

enum solution_status {
    no_roots,
    one_root,
    two_roots
};
enum input_status {
    ok_status = 0,
    wrong_format = 1,
    exit_status = -1
};

enum error_code{

};

struct solution_result{
    enum solution_status status;
    double answers[];
};

void assert_manager(enum error_code);

#endif


