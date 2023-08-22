#include "IOFunctions.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>


void show_interface(double *a, double *b, double *c){

    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    //TODO my_assert(..., err_code)
    //TODO more asserts

    printf("Enter a, b and c coefficients (a * x^2 + b * x^2 + c = 0) or q to exit: ");

    enum input_status status;
    while((status = get_input(a, b, c)) == wrong_format){
        printf("Wrong format! Please enter a, b and c coefficients or q to exit: ");
    }

    if(status == exit_status) exit(0);
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
        if(ch == EOF) return exit_status;
    }
    if(ch_count == 1 && only_q) return exit_status;
    return wrong_format;
}

void show_results(const struct solution_result *result){

    assert(result != NULL);

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
        default:
            printf("Unexpected error occuried!");
            break;
    };
}

