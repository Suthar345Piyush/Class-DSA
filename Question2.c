#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
void printArray(int arr[], int size);

// Merge function to combine two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    // Calculate sizes of two subarrays to be merged
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // Create temporary arrays
    int *leftArr = (int*)malloc(leftSize * sizeof(int));
    int *rightArr = (int*)malloc(rightSize * sizeof(int));

    // Handle memory allocation failure
    if (leftArr == NULL || rightArr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Copy data to temporary arrays leftArr[] and rightArr[]
    for (int i = 0; i < leftSize; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < rightSize; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0;      // Initial index of first subarray
    int j = 0;      // Initial index of second subarray
    int k = left;   // Initial index of merged subarray

    // Compare and merge elements from left and right subarrays
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr[], if any
    while (i < leftSize) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr[], if any
    while (j < rightSize) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // Free temporary arrays
    free(leftArr);
    free(rightArr);
}

// Recursive Merge Sort function
void mergeSort(int arr[], int left, int right) {
    // Base case: if the subarray has more than one element
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Recursively sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Utility function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function to demonstrate Merge Sort
int main() {
    // Test array with 10 integers
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 50, 75, 83};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, arrSize);

    // Perform Merge Sort
    mergeSort(arr, 0, arrSize - 1);

    printf("Sorted array:   ");
    printArray(arr, arrSize);

    return 0;
}