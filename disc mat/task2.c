#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define array_size 100

void input_array(int* a, int* size) {
    int count = 0;

    for (int i = 0; i < *size; ++i) {
        scanf("%d", a + i);

        if (*(a + i) == 0)
            break;

        ++count;
    }

    *size = count;
}

void append(int* a, int* size, int value) {
    ++* size;
    a[*size - 1] = value;
}

void output_array(int* a, int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", *(a + i));
}

void solve(int* array_first, int array_size_first, int* array_second, int array_size_second, int* result_array, int* result_array_size) {
    for (int i = 0; i < array_size_first; ++i)
        for (int j = 0; j < array_size_second; ++j)
            if (array_first[i] == array_second[j])
                append(result_array, result_array_size, array_first[i]);
}

int main() {
    int array_first[array_size];
    int array_size_first = array_size;
    input_array(array_first, &array_size_first);

    int array_second[array_size];
    int array_size_second = array_size;
    input_array(array_second, &array_size_second);

    int result_array_size = 0;
    int result_array[array_size];

    solve(array_first, array_size_first, array_second, array_size_second, result_array, &result_array_size);

    output_array(result_array, result_array_size);

    return 0;
}