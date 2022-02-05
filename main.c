#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <mem.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures//vectorVoid/vectorVoid.h"
#include <assert.h>

void myStartupFun(void) __attribute__ ((constructor));

int maxIsArr(int *a, int size) {
    int indexLeft = 0, indexRight = size - 1;
    while (indexRight != indexLeft) {
        if (a[indexLeft] <= a[indexRight]) {
            ++indexLeft;
        } else {
            --indexRight;
        }
    }
    return a[indexLeft];
}

int majorityElement(int *a, size_t size) {
    int needV = size / 2;
    for (int i = 0; i < size - 1; ++i) {
        int count = 1;
        for (int j = i + 1; j < size; ++j) {
            count += a[j] == a[i];
        }
        if (count > needV) {
            return a[i];
        }
    }
    return -1;
}

/*
void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 5);
    assert(v.size == 1);
    assert(v.capacity == 1);
    deleteVector(&v);
}

void test_pushBack_fullVector() {
    vector v = createVector(5);
    v.size = 5;
    pushBack(&v, 4);
    assert(v.size == 6);
    assert(v.capacity == 10);
    deleteVector(&v);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
    deleteVector(&v);
}

void test_popBack_emptyVector() {
    vector v = createVector(5);
    reserve(&v, 0);
    popBack(&v);
}

void test_atVector_notEmptyVector() {
    vector v = {{1, 2, 3, 4, 5}, 5, 10};
    assert(atVector(&v, 0) == v.data);
}

void test_atVector_requestToLastElement() {
    vector v = {{5, 4, 3, 2, 1}, 5, 12};
    assert(atVector(&v, 4) == v.data + 4);
}

void test_back_oneElementInVector() {
    vector v = {{1}, 1, 4};
    assert(back(&v) == v.data + v.size -1);
}

void test_front_oneElementInVector(){
    vector v = { {2},1,5};
    assert(front(&v) == v.data);
}

// "main" test function
void test() {
    test_pushBack_fullVector();
    test_pushBack_emptyVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
    printf("Accepted");
}
*/

void uniSwap (void * a , void *b,size_t size){
    void *v3 = malloc(size);
    if (v3 != NULL){
        memmove(v3,a,size);
        memmove(a,b,size);
        memmove(b,v3,size);
        free(v3);
    }
}

void uniSwap1 (void *a , void * b, size_t size){
    char * tmp = (char*)malloc(size);
    for ( int i = 0; i < size; ++i){
        tmp[i] = *((char*)a +i);
    }
    for (int i = 0; i <  size; ++i){
        *((char*)a +i) = *((char*)b+i);
    }
    for ( int i = 0; i < size; ++i){
        *((char*)b+i) = tmp[i];
    }
}

int main() {
    //strerror(errno);
    //fprintf(stdout,"%s", strerror(errno));

    //printf("%s", __FILE__);
    // find the sum of subarray

    return 0;
}