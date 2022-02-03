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

void test_pushBack_emptyVector(){
    vector v = createVector(0);
    pushBack(&v,5);
    assert(v.size == 1);
    assert(v.capacity == 1);
    deleteVector(&v);
}

void test_pushBack_fullVector(){
    vector v = createVector(5);
    v.size = 5;
    pushBack(&v,4);
    assert(v.size==6);
    assert(v.capacity == 10);
    deleteVector(&v);
}

void test_popBack_notEmptyVector(){
    vector v = createVector(0);
    pushBack(&v,10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity ==1);
    deleteVector(&v);
}

void test_popBack_emptyVector(){
    vector v = createVector(5);
    reserve(&v,0);
    popBack(&v);
}

// "main" test function
void test(){
    test_pushBack_fullVector();
    test_pushBack_emptyVector();
    test_popBack_notEmptyVector();
    printf("WORK");
}

int main() {
    //strerror(errno);
    //fprintf(stdout,"%s", strerror(errno));

    //printf("%s", __FILE__);
    // find the sum of subarray
    test();
    return 0;
}