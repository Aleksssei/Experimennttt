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

void swapMinNMaxRows(matrix m) {
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
        minValue = min(minValue, getMinValue(m.values[i] + firstColIndex, secondColIndex - firstColIndex + 1));
    }
    return minValue;
}

double getDistance(int *a, int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(a[i], 2);
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

bool isBiggerOnRight(int *a, int size) {
    if (size == 1) {
        return true;
    }
    int cmp = a[0];
    int min = a[1];
    for (int i = 2; i < size; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return cmp < min;
}

bool isLowestOnLeft(int *a, int size) {
    if (size == 1) {
        return true;
    }
    int cmp = a[size - 1];
    int max = a[size - 2];
    for (int i = size - 3; i >= 0; --i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return cmp > max;
}

int getNSpecialElement2(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            bool isLowOnLeft = isLowestOnLeft(m.values[i] + j, j + 1);
            bool isBigOnRight = isBiggerOnRight(m.values[i] + j, m.nCols - j);
            if (isLowOnLeft && isBigOnRight) {
                ++count;
            }
        }
    }
    return count;
}

double getVectorLength(int *a, int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(a[i], 2);
    }
    return sqrt(sum);
}

double getScalarProduct(int *a, int *b, int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

double getCosine(int *a, int *b, int size) {
    return getScalarProduct(a, b, size) / (getVectorLength(a, size) * getVectorLength(b, size));
}

int getVectorIndexWithMaxAngle(matrix m, int *b) {
    int minIndex = 0;
    double min = getCosine(m.values[0], b, m.nCols);
    for (int i = 1; i < m.nRows; ++i) {
        double cos = getCosine(m.values[i], b, m.nCols);
        if (cos - min < DBL_EPSILON) {
            minIndex = i;
            min = cos;
        }
    }
    return minIndex;
}

int getMaxIndexD(double *a, int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (a[i] - a[maxIndex] > DBL_EPSILON) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

position getMaxElement(matrixD m) {
    int rowMax = 0;
    int colMax = 0;
    for (int i = 0; i < m.nRows; ++i) {
        int getColIndex = getMaxIndexD(m.values[i], m.nCols);
        if (m.values[i][getColIndex] - m.values[rowMax][colMax] > DBL_EPSILON) {
            rowMax = i;
            colMax = getColIndex;
        }
    }
    return (position) {rowMax, colMax};
}

int getMinIndexD(double *a, int size) {
    int minIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] - a[minIndex] < DBL_EPSILON) {
            minIndex = i;
        }
    }
    return minIndex;
}

position getMinElement(matrixD m) {
    int rowMin = 0;
    int colMin = 0;
    for (int i = 0; i < m.nRows; ++i) {
        int findColIndex = getMinIndexD(m.values[i], m.nCols);
        if (m.values[i][findColIndex] - m.values[rowMin][colMin] < DBL_EPSILON) {
            rowMin = i;
            colMin = findColIndex;
        }
    }
    return (position) {rowMin, colMin};
}

double getSpecialScalarProduct(matrixD m) {
    double sum = 0;
    position maxElement = getMaxElement(m);
    position minElement = getMinElement(m);
    for (int i = 0; i < m.nRows; ++i) {
        sum += m.values[maxElement.rowIndex][i] * m.values[i][minElement.colIndex];
    }
    return sum;
}

void test_swapMinNMaxRows_firstMinLastMax() {
    printf("Test_swapMinNMaxRows_firstMinLastMax, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int *ptrMin = m.values[0];
    int *ptrMax = m.values[m.nRows - 1];
    swapMinNMaxRows(m);
    assert(m.values[0] == ptrMax);
    assert(m.values[m.nRows - 1] == ptrMin);
    freeMemMatrix(m);
}

void test_sortRowsByMaxElement_MedSmallLarge() {
    printf("Test_sortRowsByMaxElement_MedSmallLarge, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int *ptrMed = m.values[0];
    int *ptrSmall = m.values[1];
    int *ptrLarge = m.values[2];
    insertionSortRowsMatrixByRowCriteria(m, getMaxValue);
    assert(m.values[0] == ptrSmall);
    assert(m.values[1] == ptrMed);
    assert(m.values[2] == ptrLarge);
    freeMemMatrix(m);
}

void test_sortColsByMinElement_MedSmallLarge() {
    printf("Test_sortColsByMinElement_MedSmallLarge, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int colSmallIndex = 1;
    int colLargeIndex = 2;
    int colMedIndex = 0;
    insertionSortColsMatrixByColCriteria(m, getMinValue);
    int newColSmallIndex = 0;
    int newColMedIndex = 1;
    int newColLargeIndex = 2;
    assert(newColSmallIndex == colSmallIndex - 1);
    assert(newColMedIndex == colMedIndex + 1);
    assert(newColLargeIndex == colLargeIndex);
    freeMemMatrix(m);
}

void test_getSquareOfMatrixIfSymmetrical_isSymmetrical() {
    printf("Test_getSquareOfMatrixIfSymmetrical_isSymmetrical, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    getSquareOfMatrixIfSymmetrical(&m);
    int expectedResult[][2] = {{5, 8},
                               {8, 13}};
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            assert(expectedResult[i][j] == m.values[i][j]);
        }
    }
    freeMemMatrix(m);
}

void test_transposeIfMatrixHasNoEqualSumOfRows_notEqual() {
    printf("Test_transposeIfMatrixHasNoEqualSumOfRows_notEqual, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int expectedResult[][2] = {{1, 3},
                               {2, 4}};
    transposeIfMatrixHasNotEqualSumOfRows(&m);
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            assert(m.values[i][j] == expectedResult[i][j]);
        }
    }
    freeMemMatrix(m);
}

void test_transposeIfMatrixHasNoEqualSumOfRows_hasEqual() {
    printf("Test_transposeIfMatrixHasNoEqualSumOfRows_hasEqual, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int expectedResult[][2] = {{1, 3},
                               {2, 2}};
    transposeIfMatrixHasNotEqualSumOfRows(&m);
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            assert(m.values[i][j] == expectedResult[i][j]);
        }
    }
    freeMemMatrix(m);
}

void test_isMutuallyInverseMatrices_inverse() {
    printf("Test_isMutuallyInverseMatrices_inverse, press enter to start:");
    while (getchar() != '\n');
    printf("Select first matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    printf("Select second matrix dimensions:\n");
    int nRows1;
    printf("Number of rows:");
    scanf("%d", &nRows1);
    int nCols1;
    printf("Number of cols:");
    scanf("%d", &nCols1);
    matrix m1 = getMemMatrix(nRows1, nCols1);
    printf("Enter a matrix element:\n");
    inputMatrix(m1);
    bool result = isMutuallyInverseMatrix(m, m1);
    assert(result == 1);
    freeMemMatrix(m);
    freeMemMatrix(m1);
}

void test_isMutuallyInverseMatrices_notInverse() {
    printf("Test_isMutuallyInverseMatrices_notInverse, press enter to start:");
    while (getchar() != '\n');
    printf("Select first matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    printf("Select second matrix dimensions:\n");
    int nRows1;
    printf("Number of rows:");
    scanf("%d", &nRows1);
    int nCols1;
    printf("Number of cols:");
    scanf("%d", &nCols1);
    matrix m1 = getMemMatrix(nRows1, nCols1);
    printf("Enter a matrix element:\n");
    inputMatrix(m1);
    bool result = isMutuallyInverseMatrix(m, m1);
    assert(result == 0);
    freeMemMatrix(m);
    freeMemMatrix(m1);
}

void test_findSumOfMaxesOfPseudoDiagonal_twoOnTwoMatrix() {
    printf("Test_findSumOfMaxesOfPseudoDiagonal_twoOnTwoMatrix, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    long long result = findSumOfMaxesOfPseudoDiagonal(m);
    long long expectedResult = 5;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_findSumOfMaxesOfPseudoDiagonal_oneOnOneMatrix() {
    printf("Test_findSumOfMaxesOfPseudoDiagonal_oneOnOneMatrix, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    long long result = findSumOfMaxesOfPseudoDiagonal(m);
    long long expectedResult = 0;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_getMinInArea_maxMiddle() {
    printf("Test_getMinInArea_maxMiddle, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = getMinInArea(m);
    int expectedResult = 1;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_getMinInArea_maxRight() {
    printf("Test_getMinInArea_maxRight, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = getMinInArea(m);
    int expectedResult = 1;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_getMinInArea_maxLeft() {
    printf("Test_getMinInArea_maxLeft, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = getMinInArea(m);
    int expectedResult = 1;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_sortByDistance_matrixThreeByThree() {
    printf("Test_sortByDistance_matrixThreeByThree, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int *ptrSmall = m.values[1];
    int *ptrMed = m.values[0];
    int *ptrLarge = m.values[2];
    sortByDistance(m);
    assert(m.values[0] == ptrSmall);
    assert(m.values[1] == ptrMed);
    assert(m.values[2] == ptrLarge);
    freeMemMatrix(m);
}

void test_countEqClassesByRowsSum_allRowsAreEqual() {
    printf("Test_countEqClassesByRowsSum_allRowsAreEqual, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = countEqClassesByRowsSum(m);
    int expectedResult = 1;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_countEqClassesByRowsSum_twoClasses() {
    printf("Test_countEqClassesByRowsSum_twoClasses, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = countEqClassesByRowsSum(m);
    int expectedResult = 2;
    assert(result == expectedResult);
    freeMemMatrix(m);
}


void test_getNSpecialElement() {
    printf("Test_getNSpecialElement, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = getNSpecialElement(m);
    int expectedResult = 2;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_swapPenultimateRow_matrixThreeByThree() {
    printf("Test_swapPenultimateRow_matrixThreeByThree, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int minElementInCol = m.values[2][0];
    swapPenultimateRow(m);
    int minElementAfterSwap = m.values[1][2];
    assert(minElementAfterSwap == minElementInCol);
    freeMemMatrix(m);
}

void test_countNonDescendingRowsMatrices() {
    printf("Test_countNonDescendingRowsMatrices, press enter to start:");
    while (getchar() != '\n');
    printf("Select array of matrices dimensions:\n");
    int nMatrices;
    printf("Number of element in array:");
    scanf("%d", &nMatrices);
    int nRows;
    printf("Number of rows in each matrix:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols in each matrix:");
    scanf("%d", &nCols);
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    for (int i = 0; i < 3; ++i) {
        printf("Enter a matrix element:\n");
        inputMatrix(ms[i]);
    }
    int result = countNonDescendingRowsMatrices(ms, nMatrices);
    int expectedResult = 2;
    assert(result == expectedResult);
    freeMemMatrices(ms, nMatrices);
}

void test_countZeroRows() {
    printf("Test_countZeroRows, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = countZeroRows(m);
    int expectedResult = 1;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_getMaxNorm_matrixThreeByThree() {
    printf("Test_getMaxNorm, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrixD m = getMemMatrixD(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrixD(m);
    position maxNorm = getMaxNorm(m);
    position expectedMaxNorm = {2, 2};
    assert(m.values[maxNorm.rowIndex][maxNorm.colIndex] ==
           m.values[expectedMaxNorm.rowIndex][expectedMaxNorm.colIndex]);
    freeMemMatrixD(m);
}

void test_getNSpecialElement2() {
    printf("Test_getNSpecialElement2, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int result = getNSpecialElement2(m);
    int expectedResult = 4;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_getVectorIndexWithMaxAngles() {
    printf("Test_getVectorIndexWithMaxAngles, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrix m = getMemMatrix(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrix(m);
    int b[] = {3, 4, 5};
    int result = getVectorIndexWithMaxAngle(m, b);
    int expectedResult = 0;
    assert(result == expectedResult);
    freeMemMatrix(m);
}

void test_getSpecialScalarProduct_matrixTwoByTwo() {
    printf("Test_getSpecialScalarProduct_matrixTwoByTwo, press enter to start:");
    while (getchar() != '\n');
    printf("Select matrix dimensions:\n");
    int nRows;
    printf("Number of rows:");
    scanf("%d", &nRows);
    int nCols;
    printf("Number of cols:");
    scanf("%d", &nCols);
    matrixD m = getMemMatrixD(nRows, nCols);
    printf("Enter a matrix element:\n");
    inputMatrixD(m);
    double result = getSpecialScalarProduct(m);
    double expectedResult = 21;
    assert(fabs(result - expectedResult) < DBL_EPSILON);
    freeMemMatrixD(m);
}

void test() {
    test_swapMinNMaxRows_firstMinLastMax();
    test_sortRowsByMaxElement_MedSmallLarge();
    test_sortColsByMinElement_MedSmallLarge();
    test_getSquareOfMatrixIfSymmetrical_isSymmetrical();
    test_transposeIfMatrixHasNoEqualSumOfRows_notEqual();
    test_transposeIfMatrixHasNoEqualSumOfRows_hasEqual();
    test_isMutuallyInverseMatrices_inverse();
    test_isMutuallyInverseMatrices_notInverse();
    test_findSumOfMaxesOfPseudoDiagonal_twoOnTwoMatrix();
    test_findSumOfMaxesOfPseudoDiagonal_oneOnOneMatrix();
    test_getMinInArea_maxMiddle();
    test_getMinInArea_maxLeft();
    test_getMinInArea_maxRight();
    test_sortByDistance_matrixThreeByThree();
    test_countEqClassesByRowsSum_allRowsAreEqual();
    test_countEqClassesByRowsSum_twoClasses();
    test_getNSpecialElement();
    test_swapPenultimateRow_matrixThreeByThree();
    test_countNonDescendingRowsMatrices();
    test_countZeroRows();
    test_getMaxNorm_matrixThreeByThree();
    test_getNSpecialElement2();
    test_getVectorIndexWithMaxAngles();
    test_getSpecialScalarProduct_matrixTwoByTwo();
}

int main() {

    return 0;
}