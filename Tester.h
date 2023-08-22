#ifndef TESTER
#define TESTER
#include <cstdio>
#include <math.h>
#include "SolverUtils.h"

enum input_status clear_file_buf(FILE *file);
enum input_status read_data_chunk(FILE *fp, struct solution_result *answer, double *a, double *b, double *c);
void show_error(int test_number, const struct solution_result *right_answer, const struct solution_result *answer);
void show_test_results(int right_answers, int answers);
void print_roots(const struct solution_result *answer);
int Test(char *filename);
bool are_results_equal(struct solution_result *res1, struct solution_result *res2);
#endif
