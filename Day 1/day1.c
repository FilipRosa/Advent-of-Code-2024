#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int findMin(int* arr, const int length) {
    int min = arr[0];
    int minIndex = 0;

    for (int i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
            minIndex = i;
        }
    }

    for (int i = minIndex; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }

    return min;
}

int countDistance(const int minNumberRow1, const int minNumberRow2) {
    return abs(minNumberRow1 - minNumberRow2);
}

int sum(int* arr, const int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        sum = sum + arr[i];
    }

    return sum;
}

int findAppearance(int* arr1, int* arr2, const int length) {
    int appears = 0;

    for (int i = 0; i < length; i++) {
        int countArr2 = 0;

        for (int j = 0; j < length; j++) {
            if (arr1[i] == arr2[j]) {
                countArr2++;
            }
        }

        appears += arr1[i] * countArr2;
    }

    return appears;
}

int main() {
    FILE* file = fopen("input.txt", "rt");
    assert(file);

    int row1[1000], row2[1000], distances[1000];
    int length = 0;
    int i = 0;
    
    while(fscanf(file, "%d %d", &row1[i], &row2[i]) == 2) {
        i++;
    }

    length = i;

    fclose(file);

    int appearance = findAppearance(row1, row2, length);

    for (int i = 0; i < length; i++) {
        int minNumberRow1 = findMin(row1, length - i);
        int minNumberRow2 = findMin(row2, length - i);

        distances[i] = countDistance(minNumberRow1, minNumberRow2);
    }

    int distance = sum(distances, length);

    printf("Distance: %d\n", distance);
    printf("Appearance: %d\n", appearance);

    return 0;
}