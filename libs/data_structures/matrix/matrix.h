#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <stdbool.h>

typedef struct matrix {
    int **values;
    int nRows;
    int nCols;
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix m);

void inputMatrices(matrix *ms, int nMatrices);

void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

void insertionSortColsMatrixByColCriteria(matrix m, int(*criteria)(int *, int));

bool isSquareMatrix(matrix m);

bool twoMatricesEqual(matrix m1, matrix m2);

bool isEMatrix(matrix m);

bool isSymmetricalMatrix(matrix m);

void transposeMatrix(matrix *m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(int *a, int nRows, int nCols);

matrix *createArrayOfMatrixFromArray(int *a, int nMatrices, int nRows, int nCols);

matrix multiplyOfTwoMatrix(matrix m, matrix m1);

#endif