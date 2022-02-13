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

bool isMutuallyInverseMatrix(matrix m1, matrix m2) {
    matrix result = multiplyOfTwoMatrix(m1, m2);
    if (isEMatrix(result)) {
        return true;
    }
    return false;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long sum = 0;
    for (int i = 1; i < m.nCols; ++i) {
        int maxValue = m.values[0][i];
        for (int j = i + 1; j < m.nCols; ++j) {
            maxValue = max(maxValue, m.values[j - 1][j]);
        }
        sum += maxValue;
    }
    for (int i = 1; i < m.nRows; ++i) {
        int maxValue1 = m.values[i][0];
        for (int j = i + 1; j < m.nRows; ++j) {
            maxValue1 = max(maxValue1, m.values[j][j - 1]);
        }
        sum += maxValue1;
    }
    return sum;
}

int getMinInArea(matrix m) {
    position maxValue = getMaxValuePos(m);
    int minValue = m.values[maxValue.rowIndex][maxValue.colIndex];
    int firstColIndex = maxValue.colIndex;
    int secondColIndex = maxValue.colIndex;
    for (int i = maxValue.rowIndex - 1; i >= 0; --i) {
        if (secondColIndex + 1 > m.nCols - 1) {
            secondColIndex = m.nCols - 1;
        } else {
            ++secondColIndex;
        }
        if (firstColIndex - 1 < 0) {
            firstColIndex = 0;
        } else {
            --firstColIndex;
        }
        minValue = min(minValue, getMinValue(m.values[i] + firstColIndex, secondColIndex + 1));
    }
    return minValue;
}

double getDistance(int *a, int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }
    return sqrt(sum);
}

void insertionSortRowsMatrixByRowCriteriaD(matrix m, double (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; ++i) {
        for (int j = i; j > 0; --j) {
            if (criteria(m.values[j - 1], m.nCols) - criteria(m.values[j], m.nCols) > DBL_EPSILON) {
                swapRows(m, j - 1, j);
            }
        }
    }
}

void sortByDistance(matrix m) {
    insertionSortRowsMatrixByRowCriteriaD(m, getDistance);
}

int countEqClassesByRowsSum(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getSum);
    int count = 0;
    long long prevSum = LONG_LONG_MAX;
    for (int i = 0; i < m.nRows - 1; ++i) {
        long long sum = getSum(m.values[i], m.nCols);
        if (sum == prevSum) {
            continue;
        }
        for (int j = i + 1; j < m.nRows; ++j) {
            long long summary = getSum(m.values[j], m.nCols);
            if (summary == sum) {
                ++count;
                break;
            }
        }
        prevSum = sum;
    }
    return count;
}

int *getSubArray(matrix m, int j) {
    int *subArray = (int *) malloc(sizeof *(*m.values) * m.nRows);
    for (int i = 0; i < m.nRows; ++i) {
        subArray[i] = m.values[i][j];
    }
    return subArray;
}

int getNSpecialElement(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nCols; ++i) {
        int *subArray = getSubArray(m, i);
        int maxElement = getMaxValue(subArray, m.nRows);
        long long sum = 0;
        for (int j = 0; j < m.nRows; ++j) {
            if (subArray[j] == maxElement) {
                continue;
            }
            sum += subArray[j];
        }
        if (maxElement > sum) {
            ++count;
        }
        free(subArray);
    }
    return count;
}

int getMinIndex(int *a, int size) {
    int minIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] < a[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

position getLeftMin(matrix m) {
    int rowMin = 0;
    int colMin = 0;
    for (int i = 0; i < m.nCols; ++i) {
        int *subArray = getSubArray(m, i);
        int findRowIndex = getMinIndex(subArray, m.nRows);
        if (m.values[findRowIndex][i] < m.values[rowMin][colMin]) {
            rowMin = findRowIndex;
            colMin = i;
        }
        free(subArray);
    }
    return (position) {rowMin, colMin};
}

void swapPenultimateRow(matrix m) {
    position minValue = getLeftMin(m);
    int *subArray = getSubArray(m, minValue.colIndex);
    for (int i = 0; i < m.nRows; ++i) {
        m.values[m.nRows - 2][i] = subArray[i];
    }
    free(subArray);
}

bool isNonDescendingSorted(int *a, int size) {
    for (int i = 1; i < size; ++i) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; ++i) {
        count += isNonDescendingSorted(m.values[i], m.nCols);
    }
    return count == m.nRows;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; ++i) {
        count += hasAllNonDescendingRows(ms[i]);
    }
    return count;
}

int countZeroValues(int *a, int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        count += a[i] == 0;
    }
    return count;
}

int countZeroRows(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; ++i) {
        count += countZeroValues(m.values[i], m.nCols) == m.nCols;
    }
    return count;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int maxIndex = 0;
    int maxCount = 0;
    int firstMaxIndex = 0;
    bool flag = true;
    for (int i = 0; i < nMatrix; ++i) {
        int currCount = countZeroRows(ms[i]);
        if (currCount >= maxCount) {
            maxCount = currCount;
            maxIndex = i;
            if (flag) {
                firstMaxIndex = maxIndex;
                flag = false;
            }
        }
    }
    for (int i = firstMaxIndex; i < maxIndex + 1; ++i) {
        if (countZeroRows(ms[i]) == maxCount) {
            outputMatrix(ms[i]);
            if (i != maxIndex) {
                printf("\n");
            }
        }
    }
}

typedef struct matrixD {
    double **values;
    int nRows;
    int nCols;
} matrixD;

matrixD getMemMatrixD(int nRows, int nCols) {
    double **values = (double **) malloc(sizeof(double *) * nRows);
    for (int i = 0; i < nRows; ++i) {
        values[i] = (double *) malloc(sizeof(double) * nCols);
    }
    return (matrixD) {values, nRows, nCols};
}

matrixD *getMemArrayOfMatricesD(int nMatrices, int nRows, int nCols) {
    matrixD *arrayOfMatrices = (matrixD *) malloc(sizeof(matrixD) * nMatrices);
    for (int i = 0; i < nMatrices; ++i) {
        arrayOfMatrices[i] = getMemMatrixD(nRows, nCols);
    }
    return arrayOfMatrices;
}

void freeMemMatrixD(matrixD m) {
    for (int i = 0; i < m.nRows; ++i) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatricesD(matrixD *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        freeMemMatrixD(ms[i]);
    }
}

void inputMatrixD(matrixD m) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            scanf("%lf", *(m.values + i) + j);
        }
    }
}

void inputMatricesD(matrixD *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        inputMatrixD(*(ms + i));
        printf("\n");
    }
}

void outputMatrixD(matrixD m) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            printf("%lf ", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatricesD(matrixD *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        outputMatrixD(*(ms + i));
    }
}

int getMaxIndex(double *a, int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (fabs(a[i]) - fabs(a[maxIndex]) > DBL_EPSILON) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

position getMaxNorm(matrixD m) {
    int rowMax = 0;
    int colMax = 0;
    for (int i = 0; i < m.nRows; ++i) {
        int findColMax = getMaxIndex(m.values[i], m.nCols);
        if (fabs(m.values[i][findColMax]) - fabs(m.values[rowMax][colMax]) > DBL_EPSILON) {
            rowMax = i;
            colMax = findColMax;
        }
    }
    return (position) {rowMax, colMax};
}

void printMatrixWithLowestNorm(matrixD *ms, int nMatrix) {
    double minNorm = fabs(ms[0].values[0][0]);
    int firstNormIndex = 0;
    int normMaxIndex = 0;
    bool flag = true;
    for (int i = 0; i < nMatrix; ++i) {
        position maxNorm = getMaxNorm(ms[i]);
        if (fabs(ms[i].values[maxNorm.rowIndex][maxNorm.colIndex]) - minNorm < DBL_EPSILON) {
            minNorm = fabs(ms[i].values[maxNorm.rowIndex][maxNorm.colIndex]);
            normMaxIndex = i;
            if (flag) {
                firstNormIndex = normMaxIndex;
                flag = false;
            }
        }
    }
    for (int i = firstNormIndex; i < normMaxIndex + 1; ++i) {
        position min = getMaxNorm(ms[i]);
        if (fabs(ms[i].values[min.rowIndex][min.colIndex]) - minNorm < DBL_EPSILON) {
            outputMatrixD(ms[i]);
            if (i != normMaxIndex) {
                printf("\n");
            }
        }
    }
}

int main() {
    matrixD *ms = getMemArrayOfMatricesD(3, 2, 2);
    inputMatricesD(ms, 3);
    printMatrixWithLowestNorm(ms, 3);
    freeMemMatricesD(ms, 3);
    return 0;
}