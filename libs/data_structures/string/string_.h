#include <stdint.h>
#include <stdbool.h>

size_t myStrLen(char *s);

char *find(char *begin, char *end, int ch);

char *findNonSpace(char *begin);

char *findSpace(char *begin);

char *findNonSpaceReverse(char *rbegin, char *rend);

char *findSpaceReverse(char *rbegin, char *rend);

int myStrCmp(char *fStr, char *sStr);

char *copy(char *beginSource, char *endSource, char *beginDestination);

char *copyIf(char *beginSource, char *endSource, char *beginDestination, bool (*f)(int));

char * copyIfReverse(char *rbeginSource, const char * rendSource, char *beginDestination,bool(*f)(int));
