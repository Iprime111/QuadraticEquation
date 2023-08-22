#include "IOFunctions.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>


enum input_status request_input(double *a, double *b, double *c){
    solver_assert(a != NULL, pointer_is_null, exit_status);
    solver_assert(b != NULL, pointer_is_null, exit_status);
    solver_assert(c != NULL, pointer_is_null, exit_status);
    solver_assert(a != b, not_enough_pointers, exit_status);
    solver_assert(b != c, not_enough_pointers, exit_status);
    solver_assert(a != c, not_enough_pointers, exit_status);


    printf("Enter a, b and c coefficients (a * x^2 + b * x^2 + c = 0) or q to exit: ");

    enum input_status status;
    while((status = get_input(a, b, c)) == wrong_format){
        printf("Wrong format! Please enter a, b and c coefficients or q to exit: ");
    }

    solver_assert(status != exit_status, exit_status_found, exit_status);
    return ok_status;
}

enum input_status get_input(double *a, double *b, double *c){

    if(scanf("%lf %lf %lf", a, b, c) < 3){
        return clear_buffer();
    }
    return ok_status;
}

enum input_status clear_buffer(){
    int ch = getchar();
    int ch_count = 0;
    bool only_q = true;
    while(ch != '\n'){
        ch_count++;
        if(ch != 'q') only_q = false;
        ch = getchar();
        if(ch == EOF){
            solver_assert(ch != EOF, eof_found, exit_status)
        }
    }
    if(ch_count == 1 && only_q) return exit_status;
    return wrong_format;
}

void show_results(const struct solution_result *result){

    solver_assert(result != NULL, pointer_is_null, (void)" ");

    switch(result->status){
        case no_roots:
            printf("No real roots\n");
            break;
        case one_root:
            printf("One root: %.4lf\n", result->answers[0]);
            break;
        case two_roots:
            printf("Two roots: %.4lf %.4lf\n", result->answers[0], result->answers[1]);
            break;
        case inf_roots:
            printf("Equation has infinitely many roots\n");
            break;
        case no_result:
            solver_assert(0, not_an_equation, (void)" ");
            break;
        default:
            printf("Unexpected error occuried!");
            break;
    };
}

