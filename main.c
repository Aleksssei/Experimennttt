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

int main() {
    //strerror(errno);
    //fprintf(stdout,"%s", strerror(errno));

    //printf("%s", __FILE__);
    // find the sum of subarray

    return 0;
}