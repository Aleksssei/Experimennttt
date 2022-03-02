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

bool is_exits_element_in_array(int* a, int size, int value) {
    for (int i = 0; i < size; ++i)
        if (a[i] == value)
            return true;

    return false;
}

int solve(int* array_first, int array_size_first, int* array_second, int array_size_second) {
    int count = 0;

    for (int i = 0; i < array_size_first; ++i)
        count += is_exits_element_in_array(array_first, array_size_second, array_second[i]);

    return count;
}

int main() {
    int array_first[array_size];
    int array_size_first = array_size;
    input_array(array_first, &array_size_first);

    int array_second[array_size];
    int array_size_second = array_size;
    input_array(array_second, &array_size_second);

    int count = solve(array_first, array_size_first, array_second, array_size_second);

    printf("%d", count == 0);

    return 0;
}
