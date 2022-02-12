#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include <mem.h>
#include<windows.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; ++i) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
    }
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *arrayOfMatrices = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; ++i) {
        arrayOfMatrices[i] = getMemMatrix(nRows, nCols);
    }
    return arrayOfMatrices;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        freeMemMatrix(ms[i]);
    }
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            scanf("%d", *(m.values + i) + j);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        inputMatrix(*(ms + i));
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        outputMatrix(*(ms + i));
    }
}

static void swap(void *a, void *b, size_t baseTypeSize) {
    void *c = malloc(baseTypeSize);
    if (c) {
        memmove(c, a, baseTypeSize);
        memmove(a, b, baseTypeSize);
        memmove(b, c, baseTypeSize);
        free(c);
    }
}

void swapRows(matrix m, int i1, int i2) {
    swap(m.values + i1, m.values + i2, sizeof(*m.values));
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; ++i) {
        swap(*(m.values + i) + j1, *(m.values + i) + j2, sizeof(*(*m.values)));
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; ++i) {
        for (int j = i; j > 0; --j) {
            if (criteria(m.values[j - 1], m.nCols) > criteria(m.values[j], m.nCols)) {
                swapRows(m, j - 1, j);
            }
        }
    }
}

static int *getSubArray(matrix m, int j) {
    int *subArray = (int *) malloc(sizeof *(*m.values) * m.nRows);
    for (int i = 0; i < m.nRows; ++i) {
        subArray[i] = m.values[i][j];
    }
    return subArray;
}

void insertionSortColsMatrixByColCriteria(matrix m, int(*criteria)(int *, int)) {
    for (int i = 1; i < m.nCols; ++i) {
        for (int j = i; j > 0; --j) {
            int *fSubArray = getSubArray(m, j - 1);
            int *sSubArray = getSubArray(m, j);
            if (criteria(fSubArray, m.nRows) > criteria(sSubArray, m.nRows)) {
                swapColumns(m, j - 1, j);
            }
            free(fSubArray);
            free(sSubArray);
        }
    }
}

bool isSquareMatrix(matrix m) {
    return (m.nCols && m.nRows) && (m.nCols == m.nRows);
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows == m2.nRows && m1.nCols == m2.nRows) {
        for (int i = 0; i < m1.nRows; ++i) {
            for (int j = 0; j < m1.nCols; ++j) {
                if (m1.values[i][j] != m2.values[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool isEMatrix(matrix m) {
    if (isSquareMatrix(m)) {
        for (int i = 0; i < m.nRows; ++i) {
            if (m.values[i][i] != 1) {
                return false;
            }
            for (int j = 0; j < m.nCols; ++j) {
                if (i == j) {
                    continue;
                }
                if (m.values[i][j] != 0) { // в данном случае if эквивалентен else if
                    return false;
                }
            }
        }
        if (m.nCols && m.nRows) {
            return true;
        }
    }
    return false;
}

bool isSymmetricalMatrix(matrix m) {
    if (isSquareMatrix(m)) {
        for (int i = 0; i < m.nRows; ++i) {
            for (int j = i + 1; j < m.nCols; ++j) {
                if (m.values[j][i] != m.values[i][j]) {
                    return false;
                }
            }
        }
        if (m.nCols && m.nRows) {
            return true;
        }
    }
    return false;
}

/*void transposeSquareMatrix(matrix m){
    matrix m1= getMemMatrix(m.nCols,m.nRows);
    for ( int i = 0; i < m.nCols;++i){
        int *subArray = getSubArray(m,i);
        m1.values[i] = subArray;
    }
    for ( int i = 0; i < m.nCols; ++i){
        m.values[i] =m1.values[i];
    }
}
 */

void transposeMatrix(matrix *m) {
    matrix m1 = getMemMatrix(m->nCols, m->nRows);
    for (int i = 0; i < m->nCols; ++i) {
        int *subArray = getSubArray(*m, i);
        m1.values[i] = subArray;
    }
    *m = m1;
}

static int getMinIndex(int *a, int size) {
    int minIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] < a[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

position getMinValuePos(matrix m) {
    if (m.nCols && m.nRows) {
        int rowMin = 0;
        int colMin = 0;
        for (int i = 0; i < m.nRows; ++i) {
            int findColMin = getMinIndex(m.values[i], m.nCols);
            if (m.values[i][findColMin] < m.values[rowMin][colMin]) {
                rowMin = i;
                colMin = findColMin;
            }
        }
        return (position) {rowMin, colMin};
    }
    exit(1);
}

static int getMaxIndex(int *a, int size) {
    int maxIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] > a[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

position getMaxValuePos(matrix m) {
    if (m.nCols && m.nRows) {
        int rowMax = 0;
        int colMax = 0;
        for (int i = 0; i < m.nRows; ++i) {
            int findColMax = getMaxIndex(m.values[i], m.nCols);
            if (m.values[i][findColMax] > m.values[rowMax][colMax]) {
                rowMax = i;
                colMax = findColMax;
            }
        }
        return (position) {rowMax, colMax};
    }
    exit(1);
}

matrix createMatrixFromArray(int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            m.values[i][j] = a[k++];
        }
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(int *a, int nMatrices, int nRows, int nCols) {
    matrix *m = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int w = 0;
    for (int i = 0; i < nMatrices; ++i) {
        for (int j = 0; j < nRows; ++j) {
            for (int k = 0; k < nCols; ++k) {
                m[i].values[j][k] = a[w++];
            }
        }
    }
    return m;
}

static int getSumOfTwoArrays(int *a, int *b, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

matrix multiplyOfTwoMatrix(matrix m, matrix m1) {
    if (m.nCols == m1.nRows) {
        matrix result = getMemMatrix(m.nRows, m1.nCols);
        for (int i = 0; i < result.nRows; ++i) {
            for (int j = 0; j < result.nCols; ++j) {
                int sum = 0;
                for (int k = 0; k < m.nCols; ++k) {
                    sum += m.values[i][k] * m1.values[k][j];
                }
                result.values[i][j] = sum;
            }
        }
        return result;
    }
    fprintf(stderr, "Matrices do not multiply");
    exit(1);
}

/*matrix multiplyOfTwoMatrix(matrix m, matrix m1) {
    if (m.nCols == m1.nRows) {
        matrix result = getMemMatrix(m.nRows, m1.nCols);
        for (int i = 0; i < result.nRows; ++i) {
            for (int j = 0; j < result.nCols; ++j) {
                int *subArray = getSubArray(m1, j);
                result.values[i][j] = getSumOfTwoArrays(m.values[i], subArray, m.nCols);
                free(subArray);
            }
        }
        return result;
    }
    fprintf(stderr, "Matrices do not multiply");
    exit(1);
}
*/