#include <stdio.h>
#include <stdarg.h> 

#include "ColorConsole.h"
#include "Logger.h"

void printf_color (enum CONSOLE_COLOR color, enum CONSOLE_BOLD bold, const char *format, ...){
    AddLog;

    va_list args;
    va_start (args, bold);

    printf ("\033[%d;3%dm", bold, color);
    vfprintf (stdout, format, args);
    printf ("\033[0;39m");

    va_end (args);

    PopLog;
}

void set_color (enum CONSOLE_COLOR color, enum CONSOLE_BOLD bold){
    AddLog;
    printf ("\033[%d;3%dm", bold, color);
    PopLog;
}


