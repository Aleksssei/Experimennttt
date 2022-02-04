#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vector.h"
#include <stdlib.h>

vector createVector(size_t size) {
    int *array = (int *) malloc(sizeof(int) * size);
    if (array) {
        return (vector) {array, 0, size};
    }
    fprintf(stderr, "bad alloc");
    exit(1);
}

void reserve(vector *v, size_t newCapacity) {
    v->data = (int *) realloc(v->data, sizeof(int) * newCapacity);
    v->capacity = newCapacity;
    bool flag = newCapacity != 0;
    if (v->data == NULL && flag) {
        fprintf(stderr, "bad alloc");
        exit(1);
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->data = (int *) realloc(v->data, sizeof(int) * v->size);
}

void deleteVector(vector *v) {
    free(v->data);
}

bool isEmpty(vector *v) {
    return v->data == NULL;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void append(int *a, size_t *size, int value) {
    ++*size;
    a[*size - 1] = value;
}

void pushBack(vector *v, int value) {
    bool flag = v->size !=0;
    if (isFull(v) && flag) {
        reserve(v, 2 * v->size);
    }
    v->capacity+= !flag;
    append(v->data, &v->size, value);
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    --v->size;
}

int *atVector(vector *v, size_t index) {
    if (index > v->size - 1 || index < 0) {
        fprintf(stderr, "a[%lld] is not exist", index);
        exit(1);
    }
    return v->data + index;
}

int *back(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    return v->data + v->size -1;
}

int *front(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    return v->data;
}