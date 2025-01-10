#include <stdio.h>

// Function to calculate the average
float calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum / size;
}

// Function to find the minimum and maximum values
void findMinMax(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

// Function to count even numbers
int countEvenNumbers(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int numbers[10];
    int i, min, max, evenCount;
    float average;

    // Prompt user to input 10 numbers
    printf("Enter 10 integers:\n");
    for (i = 0; i < 10; i++) {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // Calculate the average
    average = calculateAverage(numbers, 10);

    // Find the minimum and maximum values
    findMinMax(numbers, 10, &min, &max);

    // Count even numbers
    evenCount = countEvenNumbers(numbers, 10);

    // Display results
    printf("\nResults:\n");
    printf("Average: %.2f\n", average);
    printf("Minimum value: %d\n", min);
    printf("Maximum value: %d\n", max);
    printf("Count of even numbers: %d\n", evenCount);

    return 0;
}
