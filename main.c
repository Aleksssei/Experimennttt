#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include "libs/data_structures/string/string_.h"

#define ASSERT_STRING(expected, got) assertString(expected,got, __FILE__,__FUNCTION__,__LINE__)

#define MAX_STRING_SIZE 1000

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

char _stringBuffer[MAX_STRING_SIZE];

typedef struct wordDescriptor {
    char *begin;
    char *end;
} wordDescriptor;

/*
bool getWord(char *begin, wordDescriptor *word) {
    word->begin = findNonSpace(begin);
    if (*word->begin == '\0') {
        return false;
    }
    word->end = findSpace(word->begin);
    return true;
}

void getNewWord(char *s, wordDescriptor word) {
    char *begin = s;
    while (getWord(begin, &word)) {
        char *endWord = copy(word.begin, word.end, _stringBuffer);
        char *afterDigits = copyIfReverse(endWord - 1, _stringBuffer - 1, word.begin, isdigit);
        copyIf(_stringBuffer, endWord, afterDigits, isalpha);
        begin = word.end;
    }
}
*/

bool getWord(char *s, wordDescriptor *word) {
    word->begin = findNonSpace(s);
    if (*word->begin == '\0') {
        return false;
    }
    word->end = findSpace(s);
    return true;
}

void getNewWord(char *s, wordDescriptor word) {
    char *begin = s;
    while (getWord(begin, &word)) {
        char *endWord = copy(word.begin, word.end, _stringBuffer);
        char *afterDigits = copyIf(_stringBuffer, endWord, word.begin, isdigit);
        copyIf(_stringBuffer, endWord, afterDigits, isalpha);
        begin = word.end;
    }
}


int main() {
    char s[] = "12dtyu34t";
    wordDescriptor newWord;
    getNewWord(s, newWord);
    printf("%s", s);
    return 0;
}