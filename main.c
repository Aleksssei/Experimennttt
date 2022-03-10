#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <mem.h>

#define TIME_TEST(testCode, time){ \
    clock_t start_time = clock();     \
    testCode                          \
    clock_t end_time = clock();        \
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC;\
    }

#define ARRAY_SIZE(a) sizeof a / sizeof a[0]

typedef struct sortFunc {
    void (*sort)(int *, size_t);

    char name[64];
} sortFunc;

typedef struct generatingFunc {
    void (*generate)(int *, size_t);

    char name[64];
} generatingFunc;

void swap(void *a, void *b, int sizeOfBaseType) {
    char *buff = (char *) malloc(sizeOfBaseType);
    if (buff) {
        memmove(buff, a, sizeOfBaseType);
        memmove(a, b, sizeOfBaseType);
        memmove(b, buff, sizeOfBaseType);
        free(buff);
    }
}

/*
double getTime() {
    clock_t startTime = clock();
    // fragment of code , that we test
    //
    //
    clock_t endTime = clock();
    clock_t sortTime = endTime - startTime;
    return (double) sortTime / CLOCKS_PER_SEC;
}
*/

bool isOrdered(int *a, size_t size) {
    for (int i = 0; i < size - 1; ++i) {
        if (a[i + 1] < a[i]) {
            return false;
        }
    }
    return true;
}

void outputArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", a[i]);
    }
}

void
checkTime(void (*sortFunc)(int *, size_t), void (*generateFunc)(int *, size_t), size_t size, char *experimentName) {
    static size_t runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run  #%zu | ", runCounter++);
    printf("Name : %s\n", experimentName);
    double time;
    TIME_TEST({ sortFunc(innerBuffer, size); }, time)
    printf("Status:  ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
        char *filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("An error occurred when opening the file %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");
        outputArray(innerBuffer, size);
        exit(1);
    }

}

void timeExperiment() {
    sortFunc sorts[] = {{},
                        {}};
    const unsigned numberOfFunc = ARRAY_SIZE(sorts);
    generatingFunc generatingFuncs[] = {{},
                                        {},
                                        {}};
    const unsigned numberOfGeneratingFuncs = ARRAY_SIZE(generatingFuncs);
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("--------------------------------- \n");
        printf("Size: %lld\n", size);
        for (int i = 0; i < numberOfFunc; ++i) {
            for (int j = 0; j < numberOfGeneratingFuncs; ++j) {
                static char filename[128];
                sprintf(filename, "%s_%s_time", sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf("\n");
    }
}

void bubbleSort(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            if (a[j] < a[j - 1]) {
                swap(a + j, a + j - 1, sizeof a[j]);
            }
        }
    }
}

void selectionSort(int *a, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minPos = i;
        for (int j = i + 1; j < size; ++j) {
            if (a[j] < a[minPos]) {
                minPos = j;
            }
        }
        swap(a + i, a + minPos, sizeof a[minPos]);
    }
}

void insertionSort(int *a, int size) {
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            if (a[j] < a[j - 1]) {
                swap(a + j, a + j - 1, sizeof a[j]);
            }
        }
    }
}

int main() {
    int array[] = {4, 4, 4, 3, 2, 1, 4, 5, 6};
    insertionSort(array, ARRAY_SIZE(array));
    outputArray(array, ARRAY_SIZE(array));
    return 0;
}