#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vectorVoid.h"
#include <stdlib.h>
#include <mem.h>

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

bool isEmptyV (vectorVoid *v){
    return v->data==NULL;
}

bool isFullV ( vectorVoid * v){
    return v->size == v->capacity;
}

void getVectorValueV ( vectorVoid * v,size_t index, void * dest){
    char * source = (char*)v->data + index*v->baseTypeSize;
    memmove(dest,source,v->baseTypeSize);
}

void setVectorValueV (vectorVoid *v, size_t index, void *source){
    char * dest = (char*)v->data + index*v->baseTypeSize;
    memmove(dest,source,v->baseTypeSize);
}

void popBackV ( vectorVoid * v){
    if (isEmptyV(v)){
        fprintf(stderr,"vector is empty");
        exit(1);
    }
    if ( v->size == 0){
        return;
    }
    --v->size;
}

void pushBackV(vectorVoid *v, void *source){
    bool flag = v->size !=0;
    if (isFullV(v) && flag) {
        reserveV(v, 2 * v->size);
    }
    v->capacity+= !flag;
    ++v->size;
    char *dest = (char*)v->data+(v->size-1)*v->baseTypeSize;
    //memmove(&v->data[v->size-1],source,v->baseTypeSize);
    memmove(dest,source,v->baseTypeSize);
}

