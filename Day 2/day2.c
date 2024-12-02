#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSafe(int* numbers, int columns) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 1; i < columns; i++) {
        if (numbers[i] < numbers[i - 1]) {
            decreasing = false;
        } else if (numbers[i] > numbers[i - 1]) {
            increasing = false;
        }
    }

    if (!(increasing || decreasing)) {
        return false;
    }

    for (int i = 1; i < columns; i++) {
        int dif = abs(numbers[i] - numbers[i - 1]);

        if (dif < 1 || dif > 3) {
            return false;
        }
    }

    return true;
}

bool isSafeTolerate(int* numbers, int columns) {
    for (int i = 0; i < columns; i++) {
        int* modifyNumbers = malloc((columns - 1) * sizeof(int));

        int counter = 0;

        for (int j = 0; j < columns; j++) {
            if (j != i ) {
                modifyNumbers[counter++] = numbers[j];
            }
        }

        if (isSafe(modifyNumbers, columns -1)) {
            free(modifyNumbers);
            return true;
        }

        free(modifyNumbers);
    }

    return false;
}

int main() {
    FILE* file = fopen("input.txt", "rt");
    assert(file);

    int **numbers;
    int *columns;

    int i = 0, j = 0, num;
    int counterSafe = 0;
    int counterTolerate = 0;
    int maxColumns = 0;

    numbers = malloc(1000 * sizeof(int*));
    columns = malloc(1000 * sizeof(int));
    
    while(fscanf(file, "%d", &num) != EOF) {
        if (columns[i] == 0) {
            numbers[i] = malloc(10 * sizeof(int));
        }

        numbers[i][columns[i]++] = num;

        if (fgetc(file) == '\n') {
            i++;
            columns[i] = 0;
        }
    }

    fclose(file);

    for (int i = 0; i < 1000; i++) {
        if (columns[i] == 0) {
            break;
        }

        if (isSafe(numbers[i], columns[i])) {
            counterSafe++;
        }

        if (isSafeTolerate(numbers[i], columns[i])) {
            counterTolerate++;
        }
    }

    printf("Safe: %d\n", counterSafe);
    printf("Safe with tolerate: %d\n", counterTolerate);

    for (int i = 0; i < 1000; i++) {
        free(numbers[i]);
    }

    free(numbers);
    free(columns);

    return 0;
}