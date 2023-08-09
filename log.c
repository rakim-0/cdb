#ifndef LOG
#define LOG
#include <stdio.h>

void writeOne()
{
    FILE* log = fopen("log.txt", "a");
    //fprintf(log, "Accessed Linked List: 1 second\n");
    fprintf(log, "1\n");
    fclose(log);
}

void writeTwo()
{
    FILE* log = fopen("log.txt", "a");
    //fprintf(log, "Accessed File:        2 seconds\n");
    fprintf(log, "2\n");
    fclose(log);
}
#endif
