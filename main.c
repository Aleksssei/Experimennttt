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
#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"
#include "libs/algorithms/algorithm/array.h"

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


void uniSwap(void *a, void *b, size_t size) {
    void *v3 = malloc(size);
    if (v3 != NULL) {
        memmove(v3, a, size);
        memmove(a, b, size);
        memmove(b, v3, size);
        free(v3);
    }
}

void uniSwap1(void *a, void *b, size_t size) {
    char *tmp = (char *) malloc(size);
    for (int i = 0; i < size; ++i) {
        tmp[i] = *((char *) a + i);
    }
    for (int i = 0; i < size; ++i) {
        *((char *) a + i) = *((char *) b + i);
    }
    for (int i = 0; i < size; ++i) {
        *((char *) b + i) = tmp[i];
    }
}

long long summary(int *a, int left, int right) {
    long long summary = 0;
    for (int i = left; i < right; ++i) {
        summary += a[i];
    }
    return summary;
}

long long getSumOfSubSegment(int *a, int size, int l, int r) {
    int blockSize = sqrt(size);
    int numberOfBlocks = size / blockSize;
    int *subArray = (int *) malloc(sizeof(int) * (numberOfBlocks + 1));
    int remainder = size % blockSize;
    int startIndex = 0;
    for (int i = 0; i < numberOfBlocks; ++i) {
        subArray[i] = summary(a, startIndex, startIndex + blockSize);
        startIndex += blockSize;
    }
    if (remainder) {
        subArray[numberOfBlocks] = summary(a, startIndex, size);
    }
    int leftBlockIndex = l / blockSize;
    int rightBlockIndex = r / blockSize;
    long long sum = 0;
    if (leftBlockIndex == rightBlockIndex) {
        sum += summary(a, l, r + 1);
    } else {
        sum += summary(a, l, (leftBlockIndex + 1) * blockSize);
        sum += summary(subArray, leftBlockIndex + 1, rightBlockIndex);
        sum += summary(a, rightBlockIndex * blockSize, r + 1);
    }
    free(subArray);
    return sum;
}

int sum(int *a, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }
    return sum;
}

int maxValue(int a, int b) {
    return a > b ? a : b;
}

void solveFirst(matrix m) {
    position minElement = getMinValuePos(m);
    position maxElement = getMaxValuePos(m);
    swapRows(m, minElement.rowIndex, maxElement.rowIndex);
}

int getMaxValue(int *a, int size) {
    int maxValue = a[0];
    for (int i = 0; i < size; ++i) {
        if (a[i] > maxValue) {
            maxValue = a[i];
        }
    }
    return maxValue;
}

void SortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMaxValue);
}

int getMinValue(int *a, int size) {
    int minValue = a[0];
    for (int i = 0; i < size; ++i) {
        if (a[i] < minValue) {
            minValue = a[i];
        }
    }
    return minValue;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMinValue);
}

void getSquareOfMatrixIfSymmetrical(matrix *m) {
    if (isSymmetricalMatrix(*m)) {
        *m = multiplyOfTwoMatrix(*m, *m);
    } else {
        fprintf(stderr, "matrix is not symmetrical");
        exit(1);
    }
}

long long getSum(int *a, int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }
    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    for (int i = 0; i < m->nRows - 1; ++i) {
        long long oneRowSum = getSum(m->values[i], m->nCols);
        for (int j = i + 1; j < m->nRows; ++j) {
            long long sum = getSum(m->values[j], m->nCols);
            if (oneRowSum == sum) {
                return;
            }
        }
    }
    transposeMatrix(m);
}

bool isMutuallyInverseMatrix(matrix m1, matrix m2){
    matrix result = multiplyOfTwoMatrix(m1,m2);
    if (isEMatrix(result)){
        return true;
    }
    return false;
}

// solve with help of transpose

int main() {
    matrix m = getMemMatrix(3, 3);
    outputMatrix(m);
    freeMemMatrix(m);
    return 0;
}