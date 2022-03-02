#include <stdio.h>
#include <stdbool.h>

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

void pop(int* a, int* n, const int index) {
    --* n;
    a[index] = a[*n - 1];
}

void output_array(int* a, int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", *(a + i));
}

void copy_array(int* from, int* to, int size) {
    for (int i = 0; i < size; ++i)
        to[i] = from[i];
}

void solve(int* array_first, int array_size_first, int* array_second, int array_size_second, int* result_array, int* result_array_size) {
    copy_array(array_first, result_array, array_size_first);

    int i = 0;
    int j = 0;

    while (i < array_size_first && j < array_size_second) {
        if (array_first[i] < array_second[j])
            ++i;
        else if (array_first[i] == array_second[j]) {
            pop(result_array, result_array_size, i + j);
            ++i;
            ++j;
        }
        else {
            ++j;
        }
    }

    for (int i = j; i < array_size_second; ++i)
        append(result_array, result_array_size, array_second[i]);
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
