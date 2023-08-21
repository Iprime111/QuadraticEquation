#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1.0e-6
#define SOL_SIZE(X) (sizeof(struct solution_result) + X * sizeof(double))

enum solution_status{no_roots, one_root, two_roots, solution_error};
enum input_status{ok_status = 0, wrong_format = 1, exit_status = -1};
struct solution_result{
    enum solution_status status;
    double answers[];
};


enum input_status get_input(double *a, double *b, double *c);
void show_interface(double *a, double *b, double *c);
void show_results(const struct solution_result *result);
struct solution_result *solve_equation(const double a, const double b, const double c);
int is_NaN(const double a, const double b, const double c);
int is_inf(const double a, const double b, const double c);
int is_zeroes(const double a, const double b);

int main(void){

    double a = NAN, b = NAN, c = NAN;

    show_interface(&a, &b, &c);

    struct solution_result *result = solve_equation(a, b, c);

    if(result != NULL){
        show_results(result);
        free(result);
    }
    return 0;
}

void show_interface(double *a, double *b, double *c){
    printf("Enter a, b and c coefficients (a * x^2 + b * x^2 + c = 0) or q to exit: ");

    enum input_status status;
    while((status = get_input(a, b, c)) == wrong_format){
        printf("Wrong format! Please enter a, b and c coefficients or q to exit: ");
    }

    if(status == exit_status) exit(0);
}

enum input_status get_input(double *a, double *b, double *c){
    if(scanf("%lf %lf %lf", a, b, c) < 3){
        int ch = getchar();
        int ch_count = 0;
        int only_q = 1;
        while(ch != '\n'){
            ch_count++;
            if(ch != 'q') only_q = 0;
            ch = getchar();
            if(ch == EOF) return exit_status;
        }
        if(ch_count == 1 && only_q) return exit_status;
        return wrong_format;
    }
    return ok_status;
}

struct solution_result *solve_equation(const double a, const double b, const double c){
    double d = b * b - 4 * a * c;
    struct solution_result *res = NULL;
    if(is_NaN(a, b, c) || is_inf(a, b, c) || is_zeroes(a, b)){
        res = (struct solution_result *)malloc(SOL_SIZE(0));
        res->status = solution_error;
        return res;
    }

    if(d > EPS){
        if(fabs(a) < EPS){
                res = (struct solution_result *)malloc(SOL_SIZE(1));
                res->status = one_root;
                res->answers[0] = -c / b;
        }else{
            res = (struct solution_result *)malloc(SOL_SIZE(2));
            res->status = two_roots;
            double sqroot = sqrt(d);
            res->answers[0] = (-b + sqroot) / (2 * a);
            res->answers[1] = (-b - sqroot) / (2 * a);
        }
    }else if(d < (-1 * EPS)){
        res = (struct solution_result *)malloc(SOL_SIZE(0));
        res->status = no_roots;
    }else{
        res = (struct solution_result *)malloc(SOL_SIZE(1));
        res->status = one_root;
        res->answers[0] = -b / (2 * a);
    }

    return res;
}

void show_results(const struct solution_result *result){
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
        case solution_error:
            printf("Unacceptable coefficient values!\n");
            break;
        default:
            break;
    };
}

int is_NaN(const double a, const double b, const double c){
   return (isnan(a) || isnan(b) || isnan(c) ? 1 : 0);
}

int is_inf(const double a, const double b, const double c){
    return (isinf(a) || isinf(b) || isinf(c) ? 1 : 0);
}

int is_zeroes(const double a, const double b){
    return (fabs(a) < EPS && fabs(b) < EPS ? 1 : 0);
}
