#include "IOFunctions.h"

enum INPUT_STATUS request_input (double *a, double *b, double *c){
    PushLog(1);

    solver_assert (a != NULL,   pointer_is_null, exit_status);
    solver_assert (b != NULL,   pointer_is_null, exit_status);
    solver_assert (c != NULL,   pointer_is_null, exit_status);
    solver_assert (a != b,      not_enough_pointers, exit_status);
    solver_assert (b != c,      not_enough_pointers, exit_status);
    solver_assert (a != c,      not_enough_pointers, exit_status);

    printf ("Enter a, b and c coefficients (a * x^2 + b * x^2 + c = 0) or q to exit: ");

    enum INPUT_STATUS status;
    while ((status = get_input (a, b, c)) == wrong_format){
        printf ("Wrong format! Please enter a, b and c coefficients or q to exit: ");
    }

    solver_assert (status != eof_status, eof_found, eof_status);

    RETURN status;
}

enum INPUT_STATUS get_input (double *a, double *b, double *c){
    PushLog(2);

    if(scanf("%lf %lf %lf", a, b, c) < 3){
        RETURN clear_buffer();
    }

    RETURN ok_status;
}

enum INPUT_STATUS clear_buffer (){
    PushLog(3);

    int ch = getchar ();
    int ch_count = 0;

    bool only_q = true;

    while (ch != '\n'){
        ch_count++;
        if(ch != 'q') only_q = false;

        ch = getchar();
        if(ch == EOF){
            solver_assert (ch != EOF, eof_found, eof_status);
        }
    }

    if (ch_count == 1 && only_q){
        RETURN exit_status;
    }else{
        RETURN wrong_format;
    }
}

void show_results (const struct SOLUTION_RESULT *result){
    PushLog(1);

    solver_assert (result != NULL, pointer_is_null, (void)0);

    switch (result->status){
        case no_roots:
            printf ("No real roots\n");
            break;

        case one_root:
            printf ("One root: %.4lf\n", result->answers[0]);
            break;

        case two_roots:
            printf ("Two roots: %.4lf %.4lf\n", result->answers[0], result->answers[1]);
            break;

        case inf_roots:
            printf ("Equation has infinitely many roots\n");
            break;

        case no_result:
            solver_assert (0, not_an_equation, (void)0);
            break;

        default:
            printf ("Unexpected error occuried!");
            break;
    };

    RETURN ;
}
