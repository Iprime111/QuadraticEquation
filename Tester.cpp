#include <stdio.h>
#include <math.h>

#include "Tester.h"
#include "Solver.h"
#include "ColorConsole.h"
#include "Logger.h"

int Test (char *filename){
    PushLog;

    FILE *fp = NULL;
    solver_assert ((fp = fopen (filename, "r")) != NULL, cannot_open_file, -1);
    solver_assert (ferror (fp) == 0, cannot_open_file, -1);

    struct SOLUTION_RESULT r_answer = {no_result, {NAN, NAN}};
    struct SOLUTION_RESULT answer = {no_result, {NAN, NAN}};

    int ans = 0, r_ans = 0;
    enum INPUT_STATUS status = ok_status;

    while (status == ok_status){

        double a = NAN, b = NAN, c = NAN;

        solver_assert ((status = read_data_chunk (fp, &r_answer, &a, &b, &c)) != wrong_format, exit_status_found, -1);

        if (status == exit_status)
            break;

        ans++;

        printf_color (Console_green, Console_normal, "Starting test #%d...\n", ans);

        if (Test_one_chunk (&r_answer, &answer, a, b, c)){
            show_success (ans);
            r_ans++;
        }else{
            show_error (ans, &r_answer, &answer, a, b, c);
        }
    }

    show_test_results (r_ans, ans);

    solver_assert (fclose (fp) != EOF, file_close_error, -1);

    PopLog;

    return 0;
}

bool Test_one_chunk (struct SOLUTION_RESULT *r_answer, struct SOLUTION_RESULT *answer, double a, double b, double c){
    PushLog; // TODO Push(To)Log

    solver_assert (!check_NaN_coefficients (a, b, c), number_is_nan, 0);
    solver_assert (!check_inf_coefficients (a, b, c), number_is_inf, 0);
    solver_assert (answer != NULL, pointer_is_null, 0);
    solver_assert (r_answer != NULL, pointer_is_null, 0);

    solve_equation (a, b, c, answer);

    if (are_results_equal (r_answer, answer)){
        PopLog;
        return true;
    }

    PopLog;
    return false;
}

enum INPUT_STATUS clear_file_buf (FILE *fp){
    PushLog;
    int ch = fgetc (fp);
     // TODO WRITE README!!!!

    while (ch != '\n'){
        ch = fgetc (fp);
        if (ch == EOF){
            solver_assert (ch != EOF, eof_found, exit_status);
        }
    }

    PopLog;
    return wrong_format;
}

enum INPUT_STATUS read_data_chunk (FILE *fp, struct SOLUTION_RESULT *answer, double *a, double *b, double *c){
    PushLog;
    solver_assert (answer != NULL, pointer_is_null, exit_status);
    solver_assert (fp != NULL, pointer_is_null, exit_status);
    solver_assert (a != NULL, pointer_is_null, exit_status);
    solver_assert (b != NULL, pointer_is_null, exit_status);
    solver_assert (c != NULL, pointer_is_null, exit_status);
    solver_assert (a != b, not_enough_pointers, exit_status);
    solver_assert (b != c, not_enough_pointers, exit_status);
    solver_assert (a != c, not_enough_pointers, exit_status);


    if (fscanf (fp, "COEFFS %lf %lf %lf ", a, b, c) < 3){

        solver_assert (clear_file_buf (fp) != wrong_format, wrong_data_format, wrong_format);

        PopLog;
        return exit_status;
    }

    int int_status = 0;

    solver_assert (fscanf (fp, "STATUS %d ROOTS %lf %lf ", &int_status, answer->answers, answer->answers + 1) == 3, wrong_data_format, clear_file_buf (fp));
    answer->status =  (enum SOLUTION_STATUS)int_status;

    PopLog;
    return ok_status;
}

int show_error (int test_number, const struct SOLUTION_RESULT *right_answer, const struct SOLUTION_RESULT *answer, double a, double b, double c){
    PushLog;

    solver_assert (answer != NULL,                    pointer_is_null, -1);
    solver_assert (right_answer != NULL,              pointer_is_null, -1);
    solver_assert (!check_NaN_coefficients (a, b, c), number_is_nan,   -1);
    solver_assert (!check_inf_coefficients (a, b, c), number_is_inf,   -1);

    set_color (Console_red, Console_bold);

    printf ("Error in test #%d. Expected ", test_number);
    print_roots (right_answer);
    printf (", given answer is ");
    print_roots (answer);
    printf ("\t Coefficients are %lf %lf %lf\n", a, b, c);

    set_color (Console_white, Console_normal);

    PopLog;
    return 0;
}

void show_success (int test_number){
    PushLog;
    printf_color (Console_green, Console_bold, "Test #%d passed \n", test_number);
    PopLog;
}

void print_roots (const struct SOLUTION_RESULT *answer){
    PushLog;

    printf ("%d", answer->status);

    switch (answer->status){
        case no_roots:
            break;
        case inf_roots:
            break;
        case one_root:
            printf (" %lf", answer->answers[0]);
            break;
        case two_roots:
            printf (" %lf %lf", answer->answers[0], answer->answers[1]);
            break;
        case no_result:
            break;
        default:
            solver_assert (0, wrong_data_format,  (void)" ");
            break;
    }

    PopLog;
}

void show_test_results (int right_answers, int answers){
    PushLog;
    printf ("%d tests passed out of %d!!!\n", right_answers, answers);
    PopLog;
}

bool are_results_equal (struct SOLUTION_RESULT *res1, struct SOLUTION_RESULT *res2){
    PushLog;
    if (res1->status == res2->status){
        if (res1->status == no_roots || res1->status == inf_roots){
            PopLog;
            return true;
        }else if (res1->status == one_root && !compare_doubles (res1->answers[0], res2->answers[0])){
            PopLog;
            return true;
        }else if (res1->status == two_roots &&
                !compare_doubles (res1->answers[1], res2->answers[1]) &&
                !compare_doubles (res1->answers[0], res2->answers[0])){
            PopLog;
            return true;
        }
    }
    PopLog;
    return false;
}
