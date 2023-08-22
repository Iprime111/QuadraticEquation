#include <stdio.h>
#include <math.h>
#include "Tester.h"
#include "Solver.h"

int Test(char *filename){
    FILE *fp = NULL;
    solver_assert((fp = fopen(filename, "r")) != NULL, cannot_open_file, -1); //TODO add isopen


    struct solution_result r_answer = {no_result, {NAN, NAN}};
    struct solution_result answer = {no_result, {NAN, NAN}};
    double a = NAN, b = NAN, c = NAN;
    int ans = 0, r_ans = 0;
    enum input_status status = ok_status;

    while(status == ok_status){
        solver_assert((status = read_data_chunk(fp, &r_answer, &a, &b, &c)) != wrong_format, exit_status_found, -1);

        if(status == exit_status)
            break;

        solver_assert(!check_NaN_coefficients(a, b, c), number_is_nan, -1);
        solver_assert(!check_inf_coefficients(a, b, c), number_is_inf, -1);

        solve_equation(a, b, c, &answer);

        ans++;

        if(are_results_equal(&r_answer, &answer)){
            r_ans++;
            continue;
        }

        show_error(ans, &r_answer, &answer);
    }

    show_test_results(ans, r_ans);
    return 0;
}

enum input_status clear_file_buf(FILE *fp){
    int ch = fgetc(fp);
    while(ch != '\n'){
        ch = fgetc(fp);
        if(ch == EOF){
            solver_assert(ch != EOF, eof_found, exit_status)
        }
    }
    return wrong_format;
}

enum input_status read_data_chunk(FILE *fp, struct solution_result *answer, double *a, double *b, double *c){
    solver_assert(fp != NULL, pointer_is_null, exit_status);

    if(fscanf(fp, "%lf %lf %lf ", a, b, c) < 3){
        solver_assert(clear_file_buf(fp) != wrong_format, wrong_data_format, wrong_format);
        return exit_status;
    }

    int int_status = 0;

    solver_assert(fscanf(fp, "%d %lf %lf", &int_status, answer->answers, answer->answers + 1) == 3, wrong_data_format, clear_file_buf(fp));
    answer->status = (enum solution_status)int_status;
    return ok_status;
}

void show_error(int test_number, const struct solution_result *right_answer, const struct solution_result *answer){
    printf("Error in test #%d. Expected ", test_number);
    print_roots(right_answer);
    printf(", given answer is ");
    print_roots(answer);
    printf("\n");
}

void print_roots(const struct solution_result *answer){
    printf("%d", answer->status);

    switch(answer->status){
        case no_roots:
            break;
        case inf_roots:
            break;
        case one_root:
            printf(" %lf", answer->answers[0]);
            break;
        case two_roots:
            printf(" %lf %lf", answer->answers[0], answer->answers[1]);
            break;
        case no_result:
            break;
        default:
            solver_assert(0, wrong_data_format, (void)" ");
            break;
    }
}

void show_test_results(int right_answers, int answers){
    printf("%d tests passed out of %d!!!\n", right_answers, answers);
}

bool are_results_equal(struct solution_result *res1, struct solution_result *res2){
    if(res1->status == res2->status){
        if(res1->status == no_roots || res1->status == inf_roots){
            return true;
        }else if(res1->status == one_root && !compare_doubles(res1->answers[0], res2->answers[0])){
            return true;
        }else if(res1->status == two_roots &&
                !compare_doubles(res1->answers[1], res2->answers[1]) &&
                !compare_doubles(res1->answers[0], res2->answers[0])){
        return true;
        }
    }
    return false;
}
