#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vectorVoid.h"
#include <stdlib.h>

vectorVoid createVectorV(size_t size, size_t baseTypeSize) {
    void *array = malloc(baseTypeSize * size);
    if (array) {
        return (vectorVoid) {array, 0, size, baseTypeSize};
    }
    fprintf(stderr, "bad alloc");
    exit(1);
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    v->data = realloc(v->data, v->baseTypeSize * newCapacity);
    v->capacity = newCapacity;
    bool flag = newCapacity != 0;
    if (v->data == NULL && flag) {
        fprintf(stderr, "bad alloc");
        exit(1);
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
    }
}

void shrinkToFitV(vectorVoid *v) {
    v->data = realloc(v->data, v->baseTypeSize * v->size);
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void deleteVectorV (vectorVoid * v){
    free(v->data);
}

