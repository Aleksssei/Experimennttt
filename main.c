#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include "libs/data_structures/string/string_.h"

#define ASSERT_STRING(expected, got) assertString(expected,got, __FILE__,__FUNCTION__,__LINE__)

#define MAX_STRING_SIZE 1000
#define MAX_N_WORDS_IN_STRING 1000
#define MAX_WORD_SIZE 50

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

bool getWordReverse(char *rbegin, char *rend, wordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend) + 1;
    if (*word->end == *rend) {
        return false;
    }
    word->begin = findSpaceReverse(word->end - 1, rend);
    return true;
}

// FOURTH

bool getDigitPos(char *s, char **digitPos) {
    while (*s != '\0') {
        if (isdigit(*s)) {
            *digitPos = s;
            return true;
        }
        ++s;
    }
    return false;
}

void getSpaceWord(char *s) {
    char *begin = s;
    char *digitPos;
    char *digitPosForBuff;
    char *endString = copy(s, s + myStrLen(s) + 1, _stringBuffer);
    char *beginStringBuffer = _stringBuffer;
    while (getDigitPos(begin, &digitPos)) {
        int numbOfIterate = *digitPos - '0';
        for (int i = 0; i < numbOfIterate; ++i) {
            *digitPos = ' ';
            ++digitPos;
        }
        begin = digitPos;
        getDigitPos(beginStringBuffer, &digitPosForBuff);
        copy(digitPosForBuff + 1, endString, digitPos);
        beginStringBuffer = digitPosForBuff + 1;
    }
}

// fifth



int main() {
    char s[MAX_WORD_SIZE] = "9t2y3u92";
    getSpaceWord(s);
    int count = 0;
    for (int i = 0; i < myStrLen(s); ++i) {
        count += s[i] == ' ';
    }
    printf("%d\n", count);
    printf("%s\n", s);
    return 0;
}