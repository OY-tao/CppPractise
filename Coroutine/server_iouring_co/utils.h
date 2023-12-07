#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cstring>
#include <cstdio>

constexpr int group_id = 1337;

/*
 * Utility function to convert a string to lower case.
 * */

void strtolower(char *str) {
    for (; *str; ++str)
        *str = (char)tolower(*str);
}
/*
 One function that prints the system call and the error details
 and then exits with error code 1. Non-zero meaning things didn't go well.
 */
void fatal_error(const char *syscall) {
    perror(syscall);
    exit(1);
}

#define log(...) do { printf(__VA_ARGS__); putchar('\n'); fflush(stdout); } while(0)

#endif