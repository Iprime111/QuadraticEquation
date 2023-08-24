#include <cstdio>
#include <string.h>
#include <cstdlib>

#include "Logger.h"
#include "SolverUtils.h"
#include "ColorConsole.h"

struct LOGGED_FUNCTION *Stack_trace_buffer;
static int FunctionsCount = 0;

void add_func_to_log (const char *file, const char *function, int line){

    solver_assert (file != NULL, pointer_is_null, (void)" ");
    solver_assert (function != NULL, pointer_is_null, (void)" ");
    solver_assert (strlen (file) < FILENAME_MAX, length_too_big, (void)" ");
    solver_assert (strlen (file) < FILENAME_MAX, length_too_big, (void)" ");

    if (FunctionsCount >= TRACE_BUFFER_SIZE)
        return;

    strcpy (Stack_trace_buffer[FunctionsCount].file, file);
    strcpy (Stack_trace_buffer[FunctionsCount].function, function);
    Stack_trace_buffer[FunctionsCount].line = line;
    FunctionsCount++;
}

void Show_stack_trace (){
    for (int i = FunctionsCount - 1; i >= 0; i--){
        printf_color (Console_default, Console_bold, "line: %d in function: %s in file: \"%s\"\n",\
            Stack_trace_buffer[i].line, Stack_trace_buffer[i].function, Stack_trace_buffer[i].file);
    }
}

void pop_func_from_log (){
    FunctionsCount--;
}

void open_log(){
    Stack_trace_buffer = (struct LOGGED_FUNCTION*)calloc(TRACE_BUFFER_SIZE, sizeof(LOGGED_FUNCTION));
}

void close_log(){
    free(Stack_trace_buffer);
}

