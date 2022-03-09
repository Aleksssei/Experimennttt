#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include "string_.h"

size_t myStrLen(char *s) {
    char *end = s;
    while (*end != '\0') {
        ++end;
    }
    return end - s;
}

char *find(char *begin, const char *end, int ch) {
    while (begin != end && *begin != ch) {
        ++begin;
    }
    return begin;
}

char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        ++begin;
    }
    return begin;
}

char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin)) {
        ++begin;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && isspace(*rbegin)) {
        --rbegin;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !isspace(*rbegin)) {
        --rbegin;
    }
    return rbegin;
}

int myStrCmp(char *fStr, char *sStr) {
    while (*fStr != '\0' && *sStr != '\0' && *fStr++ == *sStr++);
    return *fStr - *sStr;
}

char *copy(char *beginSource, const char *endSource, char *beginDestination) {
    //while (beginSource != endSource) {
    // *beginDestination++ = *beginSource++;
    //}
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    return beginDestination + size;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, bool (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination++ = *beginSource;
        }
        ++beginSource;
    }
    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, bool(*f)(int)) {
    while (rbeginSource != rendSource) {
        if (f(*rbeginSource)) {
            *beginDestination++ = *rbeginSource;
        }
        --rbeginSource;
    }
    return beginDestination;
}




