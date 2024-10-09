#include <stdio.h>
#include <cstdlib>
#include <ctime>

void populate(float* arr, int size) {
    // naive approach
    for (int i = 0; i < size; i++) {
        arr[i] = (static_cast<float>(rand()) / RAND_MAX) * 255.0f;
    }
}

void merge(float* left, float* right, float* arr, int size) {

    int leftSize = size / 2;
    int rightSize = size - leftSize;

    int i = 0, l = 0, r = 0;    // position in the loop for a base, left and right arrays

    while(l < leftSize && r < rightSize) {
        // if the number on the left is smaller than the number on the right
        // we copy the left element first
        // e.g. 3 is smaller than 4, hence we copy 3
        if (left[l] < right[r]) {
            arr[i++] = left[l++];
        }
        // otherwise copy the right one
        else {
            arr[i++] = right[r++];
        }

    }
    
    while(l < leftSize) {
        arr[i++] = left[l++];
    }
    while(r < rightSize) {
        arr[i++] = right[r++];
    }
}

void sort(float* arr, int size) {
    // sequential approach
    if (size <= 1) return;  // divides the array in two until the size is 1

    int middle = size / 2;  // determine the middle point to divide the base array in left and right subarrays

    float* left  = new float[middle]{ };
    float* right = new float[size - middle]{ };

    // divides the base array in two
    for (int i = 0; i < middle; i++) {
        left[i] = arr[i];
    }
    for (int i = 0; i < size - middle; i++) {
        right[i] = arr[middle + i];
    }

    // recurse arrays
    sort(left, middle);
    sort(right, size - middle);

    merge(left, right, arr, size);

    delete[] right;
    delete[] left;
}

void print(float* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main() {

    std::srand(std::time(0));

    int size = 10;
    float* arr = new float[size]{ };

    printf("Populating the array of size %i with random numbers...\n", size);
    populate(arr, size);
    print(arr, size);
    printf("Array has been populated successfully.\n");

    
    printf("Sorting...\n");
    sort(arr, size);
    print(arr, size);
    printf("Numbers have been sorted successfully.\n");


    delete[] arr;
    return 0;
}