#ifndef INC_VECTORVOID_H
#define INC_VECTORVOID_H

#include <limits.h>
#include <stdbool.h>

typedef struct vectorVoid{
    void *data;
    size_t size;
    size_t capacity;
    size_t baseTypeSize;
} vectorVoid;









#endif