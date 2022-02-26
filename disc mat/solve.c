#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "libs/data_structures/string/string_.h"

void inputArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        scanf("%d", a + i);
    }
}

void outputArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", *(a + i));
    }
}

void append(int *a, int *size, int value) {
    ++*size;
    a[*size - 1] = value;
}

bool isAlreadyExist(int *a, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (a[i] == value) {
            return true;
        }
    }
    return false;
}

void deleteElem(int *a, int *size, int pos) {
    a[pos] = a[*size - 1];
    --*size;
}

void solve() { // универсальный способ решения 4-ой задачи ( подходит для повторяющихся чисел)
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arraySize + arrSize]; // предельный случай
    int copyArraySize = arraySize;
    int copyArrSize = arrSize;
    for (int i = 0; i < copyArraySize; ++i) {
        bool flag = false;
        for (int j = 0; j < copyArrSize; ++j) {
            if (array[i] == arr[j]) {
                deleteElem(arr, &arrSize, j);
                flag = true;
            }
        }
        if (flag) {
            deleteElem(array, &arraySize, i);
        }
    }
    for (int i = 0; i < arraySize; ++i) {
        append(solveArray, &solveArraySize, array[i]);
    }
    for (int i = 0; i < arrSize; ++i) {
        append(solveArray, &solveArraySize, arr[i]);
    }
    outputArray(solveArray, solveArraySize);
}

void solveFirstQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arrSize + arraySize];
    for (int i = 0; i < arraySize; ++i) {
        append(solveArray, &solveArraySize, array[i]);
    }
    for (int i = 0; i < arrSize; ++i) {
        if (!isAlreadyExist(array, arraySize, arr[i])) {
            append(solveArray, &solveArraySize, arr[i]);
        }
    }

    outputArray(solveArray, solveArraySize);
}

void solveSecondQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int size = min(arraySize,arrSize); // предельный случай , когда один массив является подмножеством другого ( больший является
    // надмножеством по отношению к первому
    int solveArray[size];
    for ( int i = 0;i  <arraySize; ++i){
        for ( int j = 0; j < arrSize; ++j){
            if (array[i] == arr[j]){
                append(solveArray,&solveArraySize,array[i]);
            }
        }
    }
    outputArray(solveArray,solveArraySize);
}

void solveThirdQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arraySize]; // предельный случай
    int copyArraySize = arraySize;
    for (int i = 0; i < copyArraySize; ++i) {
        if (!isAlreadyExist(arr, arrSize, array[i])) {
            append(solveArray,&solveArraySize,array[i]);
        }
    }
    outputArray(solveArray, solveArraySize);
}

void solveFourthQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arraySize + arrSize]; // предельный случай
    int copyArraySize = arraySize;
    int copyArrSize = arrSize;
    for (int i = 0; i < copyArraySize; ++i) {
        for (int j = 0; j < copyArrSize; ++j) {
            if (array[i] == arr[j]) {
                deleteElem(array,&arraySize,i);
                deleteElem(arr,&arrSize,j);
                break;
            }
        }
    }
    for ( int i =  0; i < arraySize; ++i){
        append(solveArray,&solveArraySize,array[i]);
    }
    for ( int i = 0; i < arrSize; ++i){
        append(solveArray,&solveArraySize,arr[i]);
    }
    outputArray(solveArray, solveArraySize);
}

void solveFifthQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);

    int count = !(arraySize&&arrSize);
    for ( int i = 0; i < arraySize;++i){
        if (isAlreadyExist(arr,arrSize,array[i])){
            ++count;
        }
    }
    bool ans = count == arraySize;
    printf ("%d", ans);
}

void solveSixthQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);

    int compSize = max(arrSize,arraySize);
    int count = compSize==0;
    for ( int i = 0; i < arraySize; ++i){
        if (isAlreadyExist(arr,arrSize,array[i])){
            ++count;
        }
    }
    bool ans = count == compSize;
    printf("%d", ans);
}

void solveSevenQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);

    bool flag = true;
    for ( int i = 0; i  < arraySize; ++i){
        for ( int j = 0; j < arrSize; ++j){
            if ( array[i] ==arr[j]){
                flag = false;
                goto mark;
            }
        }
    }
    mark:
    printf("%d", flag);
}

void solveEight(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arraySize + arrSize]; // предельный случай
    int i = 0;
    int j = 0;
    int * copyArray = array;
    int * copyArr = arr;
    int remainderArray = 0;
    int remainderArr = 0;
    while (i < arraySize || j < arrSize){
        if (i==arraySize){
            --i;
            copyArray[i] = array[i];
            array[i] = INT_MAX;
            remainderArray = i;
        }
        if ( j ==arrSize){
            --j;
            copyArr[j] =arr[j];
            arr[j] = INT_MAX;
            remainderArr = j;
        }
        if (array[i] < arr[j]){
            append(solveArray,&solveArraySize,array[i]);
            ++i;
        }
        else if (array[i] == arr[j]){
            append(solveArray,&solveArraySize,array[i]);
            append(solveArray,&solveArraySize,arr[j]);
            ++i;
            ++j;
        }
        else{
            append(solveArray,&solveArraySize,arr[j]);
            ++j;
        }
    }
    array[remainderArray] = copyArray[remainderArray];
    arr[remainderArr] = copyArr[remainderArr];
    solveArraySize = arraySize+arrSize;
    outputArray(solveArray,solveArraySize);
}

void solveNinthQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int size = min(arrSize,arraySize);
    int solveArray[size]; // предельный случай
    int i = 0;
    int j = 0;
    while ( i < arraySize && j < arrSize){
        if ( array[i] < arr[j]){
            ++i;
        }
        else if (array[i] == arr[j]){
            append(solveArray,&solveArraySize,array[i]);
            ++i;
            ++j;
        }
        else{
            ++j;
        }
    }
    outputArray(solveArray,solveArraySize);
}

void solveTenthQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arraySize]; // предельный случай
    int i = 0;
    int j = 0;
    int *copyArr = arr;
    int remainderArr = 0;
    while (i < arraySize) {
        if (j == arrSize) {
            --j;
            copyArr[j] = arr[j];
            arr[j] = INT_MAX;
            remainderArr = j;
        }
        if (array[i] < arr[j]) {
            append(solveArray, &solveArraySize, array[i]);
            ++i;
        } else if (array[i] == arr[j]) {
            ++i;
            ++j;
        } else {
            ++j;
        }
    }
    arr[remainderArr] = copyArr[remainderArr];
    outputArray(solveArray, solveArraySize);
}

void solveEleventhQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int solveArraySize = 0;
    int solveArray[arraySize + arrSize]; // предельный случай
    int i = 0;
    int j = 0;
    int * copyArray = array;
    int * copyArr = arr;
    int remainderArray = 0;
    int remainderArr = 0;
    while (i < arraySize || j < arrSize){
        if (i==arraySize){
            --i;
            copyArray[i] = array[i];
            array[i] = INT_MAX;
            remainderArray = i;
        }
        if ( j ==arrSize){
            --j;
            copyArr[j] =arr[j];
            arr[j] = INT_MAX;
            remainderArr = j;
        }
        if (array[i] < arr[j]){
            append(solveArray,&solveArraySize,array[i]);
            ++i;
        }
        else if (array[i] == arr[j]){
            ++i;
            ++j;
        }
        else{
            append(solveArray,&solveArraySize,arr[j]);
            ++j;
        }
    }
    array[remainderArray] = copyArray[remainderArray];
    arr[remainderArr] = copyArr[remainderArr];
    outputArray(solveArray,solveArraySize);
}

void solveTwelfthQuest(){
    int arraySize;
    scanf("%d", &arraySize);

    int array[arraySize];
    int arrSize;
    scanf("%d", &arrSize);

    int arr[arrSize];
    inputArray(array, arraySize);
    inputArray(arr, arrSize);
    int i = 0;
    int j = 0;
    int count = !(arraySize&&arrSize);
    while (i < arraySize) {
        if (array[i] < arr[j]) {
            ++i;
        } else if (array[i] == arr[j]) {
            ++i;
            ++j;
            ++count;
        } else {
            ++j;
        }
    }
    bool ans = count == arraySize;
    printf("%d", ans);
}
