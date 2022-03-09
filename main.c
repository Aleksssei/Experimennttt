#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include "libs/data_structures/string/string_.h"
#include <assert.h>

#define ASSERT_STRING(expected, got) assertString(expected,got, __FILE__,__FUNCTION__,__LINE__)

#define MAX_STRING_SIZE 1000
#define MAX_N_WORDS_IN_STRING 1000
#define MAX_WORD_SIZE 100

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


bool getWord(char *s, wordDescriptor *word) {
    word->begin = findNonSpace(s);
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

bool areTwoWordsAreEqual(char *firstBegin, const char *firstEnd, char *secondBegin, const char *secondEnd) {
    size_t firstSize = firstEnd - firstBegin;
    size_t secondSize = secondEnd - secondBegin;
    if (firstSize == secondSize) {
        int i = 0;
        while (i < firstSize && *firstBegin++ == *secondBegin++) {
            ++i;
        }
        return i == firstSize;
    }
    return false;
}

void replaceOneByOne(char *s, char *w1, char *w2, wordDescriptor word) {
    char *endString = copy(s, s + myStrLen(s) + 1, _stringBuffer);
    char *begin = s;
    char *endOfW2 = w2 + myStrLen(w2);
    char *endOfW1 = w1 + myStrLen(w1);
    wordDescriptor wordFromBuffer;
    char *beginOfBuffer = _stringBuffer;
    bool isZeroSymbol = false;
    while (getWord(begin, &word)) {
        if (*word.end == '\0') {
            isZeroSymbol = true;
        }
        if (areTwoWordsAreEqual(word.begin, word.end, w1, endOfW1)) {
            char *copyOfW2 = w2;
            while (copyOfW2 != endOfW2) {
                *word.begin = *copyOfW2;
                ++word.begin, ++copyOfW2;
            }
            getWord(beginOfBuffer, &wordFromBuffer);
            copy(wordFromBuffer.end, endString, word.begin);
            beginOfBuffer = wordFromBuffer.end;
        }
        begin = word.begin;
    }
}

bool isOrderedString(char *beginString) {
    wordDescriptor previousWord, currentWord;
    getWord(beginString, &previousWord);
    beginString = previousWord.end;
    while (getWord(beginString, &currentWord)) {
        if (areTwoWordsAreEqual(previousWord.begin, previousWord.end, currentWord.begin, currentWord.end)) {
            return false;
        } else {
            previousWord = currentWord;
            beginString = currentWord.end;
        }

    }
    return true;
}

void printReversedWords(char *string) {
    char *endOfStr = copy(string, getEndOfString(string), _stringBuffer);
    *endOfStr = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    char *begin = string;
    for (int i = 0; i < _bag.size; ++i) {
        char *reverseCopyEnd = copyIfReverse(_bag.words[i].end - 1, _bag.words[i].begin - 1, begin);
        *reverseCopyEnd = '\0';
        printf("%s\n", begin);
    }
}

bool isPalindrome(wordDescriptor word) {
    --word.end;
    int len = word.end - word.begin;
    if (len % 2 == 0)
        return false;
    for (int i = 0; i < len; ++i)
        if (*word.begin != *word.end)
            return false;
        else {
            ++word.begin;
            --word.end;
        }
    return true;
}

int countOfPalindromes(char *beginString) {
    int result = 0;
    wordDescriptor word;;
    while (getcommaInWord(beginString, &word)) {
        result += isPalindrome(word);
        beginString = word.end;
    }
    return result;
}

void getMergedString(char *s, char *s1, char *s2) {
    char *beginDestination = s;
    wordDescriptor word, word1;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1;
    char *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word)), (isW2Found = getWord(beginSearch2, &word1)), isW1Found ||
                                                                                                    isW2Found) {
        if (isW1Found) {
            beginDestination = copy(word.begin, word.end, beginDestination);
            *(beginDestination++) = ' ';
            beginSearch1 = word.end;
        }
        if (isW2Found) {
            beginDestination = copy(word1.begin, word1.end, beginDestination);
            *(beginDestination++) = ' ';
            beginSearch2 = word1.end;
        }
    }
    *(--beginDestination) = '\0';
}

void getReverseWord(char *s) {
    char *endOfStr = copy(s, getEndOfString(s), _stringBuffer);
    char *copyBegin = s;
    char *beginSearch = endOfStr - 1;
    wordDescriptor word;
    while (getWordReverse(beginSearch, _stringBuffer - 1, &word)) {
        copyBegin = copy(word.begin, word.end, copyBegin);
        *copyBegin++ = ' ';

        char *startNextWord = beginSearch - word.end + word.begin - 1;
        beginSearch = findNonSpaceReverse(startNextWord, _stringBuffer - 1);
    }
    *copyBegin = '\0';
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, char **beginOfWord, char **endOfWord) {
    char *begin = s;
    wordDescriptor word;
    getBagOfWords(&_bag, begin);
    if (!getWord(s, &word))
        return EMPTY_STRING;
    if (find(_bag.words[0].begin, _bag.words[0].end, 'a') != _bag.words[0].end ||
        find(_bag.words[0].begin, _bag.words[0].end, 'A') != _bag.words[0].end)
        return FIRST_WORD_WITH_A;
    for (int i = 1; i < _bag.size; i++) {
        if (find(_bag.words[i].begin, _bag.words[i].end, 'a') != _bag.words[i].end ||
            find(_bag.words[i].begin, _bag.words[i].end, 'A') != _bag.words[i].end) {
            *beginWordBefore = _bag.words[i - 1].begin;
            *endWordBefore = _bag.words[i - 1].end;
            return WORD_FOUND;
        }
    }
    return (WordBeforeFirstWordWithAReturnCode) NOT_FOUND_A_WORD_WITH_A;
}

wordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    *wordBegin = _bag2.words;
    wordDescriptor *wordEnd = _bag.words + _bag.size - 1;
    while (_bag.words <= wordEnd) {
        wordDescriptor *wBegin = wordBegin;
        while (wBegin < _bag2.words + _bag2.size) {
            if (!areTwoWordsEqual(*wordEnd, *wBegin)) {
                return *wordEnd;
            }
            ++wBegin;
        }
        --wordEnd;
    }
    return (wordDescriptor) {0, 0};
}


bool isStringHasEqualWords(char *s) {
    getBagOfWords(&_bag, s);
    wordDescriptor *wordBegin = _bag.words;
    wordDescriptor *wordEnd = _bag.words + _bag.size - 1;
    while (wordBegin < wordEnd) {
        wordDescriptor *wBegin = wordBegin + 1;
        while (wBegin <= wordEnd) {
            if (areTwoWordsEqual(*wordBegin, *wBegin)) {
                return true;
            }
            ++wBegin;
        }
        ++wordBegin;
    }
    return false;
}

int compare_char(const void *a, const void *b) {
    char arg1 = *(const char *) a;
    char arg2 = *(const char *) b;
    return arg1 - arg2;
}

bool hasWordsFromEqualsChar(char *s) {
    char *endOfBuf = copy(s, getEndOfString(s), _stringBuffer);
    *endOfBuf = '\0';
    char *startWord = _stringBuffer;
    wordDescriptor word;
    while (getWord(startWord, &word)) {
        qsort(word.begin, word.end - word.begin, sizeof(char), compare_char);
        startWord = word.end;
    }
    return isStringHasEqualWords(_stringBuffer);
}

void getStringFromWords(char *s) {
    wordDescriptor currentWord, lastWord;
    char *startWord = s;
    char *stringWriter = s;
    char *endOfBuff = copy(s, getEndOfString(s), _stringBuffer);
    *endOfBuff = '\0';
    getWordReverse(endOfBuff - 1, _stringBuffer - 1, &lastWord);
    while (getWord(startWord, &currentWord)) {
        if (areTwoWordsEqual(lastWord, currentWord)) {
            stringWriter = copy(currentWord.begin, currentWord.end, stringWriter);
            *stringWriter++ = ' ';
        }
        startWord = currentWord.end;
    }
    *stringWriter = '\0';
}


void test_removeNonLetters_withoutSpace() {
    char s[] = "ByeWorld";
    removeNonLetters(s);
    ASSERT_STRING("ByeWorld", s);
}

void test_removeNonLetters_withSpace() {
    char s[] = "Bye World";
    removeNonLetters(s);
    ASSERT_STRING("ByeWorld", s);
}

void test_removeNonLetters() {
    test_removeNonLetters_withoutSpace();
    test_removeNonLetters_withSpace();
}


void test_removeAdjacentEqualLetters() {
    char s[] = "ssss yy";
    removeAdjacentEqualLetters(s);
    ASSERT_STRING("s y", s);
}

void test_getNewWord() {
    char s[] = "123ABC";
    getNewWord(s);
    ASSERT_STRING("123ABC", s);
}

void test_getSpaceWord() {
    char s[MAX_STRING_SIZE] = "1a2b3c";
    getSpaceWord(s);
    ASSERT_STRING(" a  b   c", s);
}

void test_replace() {
    char s[] = "Bye World";
    wordDescriptor word;
    replaceOneByOne(s, "Bye", "Hello", word);
    ASSERT_STRING("Hello World", s);
}

void test_isOrderedString() {
    char s[] = "3 4 5";
    assert(isOrderedString(s) == true);
}

void test_printReversedWords() {
    char s[] = "Word Hello";
    printReversedWords(s);
}

void test_getCountPalindroms() {
    char s[] = "rtyytr tyyt";
    assert(2 == countOfPalindromes(s));
}

void test_getMergedString() {
    char s1[] = "1 1 1";
    char s2[] = "3 5 7";
    char buff[12];
    getMergedString(buff, s1, s2);
    ASSERT_STRING("1 1 1 3 5 7", buff);
}

void test_getReverseWord() {
    char s[20] = "World Hello";
    getReverseWord(s);
    ASSERT_STRING("Hello World", s);
}

void test_getWordBeforeFirstWordWithA() {
    char *beginWord, *endWord;

    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &beginWord, &endWord) == EMPTY_STRING);

    char s2[] = " AHJYTR";
    assert(getWordBeforeFirstWordWithA(s2, &beginWord, &endWord) == FIRST_WORD_WITH_A);

    char s3[] = "HELLO A";
    assert(getWordBeforeFirstWordWithA(s3, &beginWord, &endWord) == WORD_FOUND);
    char got[MAX_WORD_SIZE];
    copy(beginWord, endWord, got);
    got[endWord - beginWord] = '\0';
    ASSERT_STRING("BC", got);

    char s4[] = "rjg YUK QWE YU";
    assert(getWordBeforeFirstWordWithA(s4, &beginWord, &endWord) == NOT_FOUND_A_WORD_WITH_A);
}

void test_lastWordInFirstStringInSecondString() {
    char s1[] = "4";
    char s2[] = "1 2 3 4 5 6";
    wordDescriptor word = lastWordInFirstStringInSecondString(s1, s2);
    char result[MAX_STRING_SIZE];
    wordDescriptorToString(word, result);
    ASSERT_STRING("4", result);
}

void test_isStringHasEqualWords1() {
    char s[MAX_STRING_SIZE] = "Hello Hello";
    assert(isStringHasEqualWords(s) == true);
}

void test_isStringHasEqualWords2() {
    char s[MAX_STRING_SIZE] = "Hello hello";
    assert(isStringHasEqualWords(s) == false);
}

void test_hasWordsFromEqualsChar() {
    assert(hasWordsFromEqualsChar("Hello eHlol"));
}

void test_getStringFromWords() {
    char str[] = "Bye delta Bye";

    getStringFromWords(str);
    ASSERT_STRING(str, "delta");
}

void test() {
    test_removeNonLetters();
    test_removeAdjacentEqualLetters();
    test_removeNonLetters_withSpace();
    test_removeNonLetters_withoutSpace();
    test_getNewWord();
    test_getSpaceWord();
    test_replace();
    test_isOrderedString();
    test_printReversedWords();
    test_getCountPalindroms();
    test_getMergedString();
    test_getReverseWord();
    test_getWordBeforeFirstWordWithA();
    test_lastWordInFirstStringInSecondString();
    test_isStringHasEqualWords1();
    test_isStringHasEqualWords2();
    test_hasWordsFromEqualsChar();
    test_getStringFromWords();
    printf("Accepted");
}

int main() {
    test();
    return 0;
}