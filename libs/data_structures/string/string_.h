#include <stdint.h>
#include <stdbool.h>

size_t myStrLen(char *s);

char *find(char *begin, const char *end, int ch);

char *findNonSpace(char *begin);

char *findSpace(char *begin);

char *findNonSpaceReverse(char *rbegin, const char *rend);

char *findSpaceReverse(char *rbegin, const char *rend);

int myStrCmp(char *fStr, char *sStr);

char *copy(char *beginSource, const char *endSource, char *beginDestination);

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, bool (*f)(int));

char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, bool(*f)(int));
