#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include "libs/data_structures/string/string_.h"

#define ASSERT_STRING(expected, got) assertString(expected,got, __FILE__,__FUNCTION__,__LINE__)


void assertString(const char *expected, const char *got, const char *fileName, const char *funcName, int line) {
    if (myStrCmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: %s\n", expected);
        fprintf(stderr, "Got: %s\n", got);
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

/*
void startWork(void)__attribute__((constructor()));

void finishWork(void)__attribute__((destructor()));

void startWork(void){
    printf("Do some job\n");
}

void finishWork(void){
    printf("\n The work is done");
}
*/

// FIRST
char *getEndOfString(char *s) {
    char *copyS = s;
    while (*copyS != '\0') {
        ++copyS;
    }
    return copyS;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

//SECOND

bool isNextNotEqual(char *s) {
    char *copyS = s;
    return *s != *++copyS;
}

char *copyIfS(char *beginSource, const char *endSource, char *beginDestination, bool (*f)(char *)) {
    while (beginSource != endSource) {
        if (f(beginSource)) {
            *beginDestination++ = *beginSource;
        }
        ++beginSource;
    }
    return beginDestination;
}

void removeAdjacentEqualLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIfS(s, endSource, s, isNextNotEqual);
    *destination = '\0';
}

//third



int main() {
    char s[] = "     sssssss     ";
    removeAdjacentEqualLetters(s);
    printf("%s", s);
    return 0;
}