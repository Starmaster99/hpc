#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>

#define SIZE 100000000

void populate(float* arr, int size) {
    //std::random_device{}()
    std::mt19937 gen(69);
    std::uniform_real_distribution<> dis(0.0, 255.0);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
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

std::string formatNumber(uint64_t num) {
    std::string str = std::to_string(num);

    int insertPos = str.length() - 3;
    while(insertPos > 0) {
        str.insert(insertPos, ",");
        insertPos -= 3;
    }

    return str;
}

void print(float* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}


std::string formatDuration(uint64_t durationUs) {
    if (durationUs < 10) {
        return "<0 µs";
    }
    else if(durationUs < 1000) {
        return std::to_string(static_cast<double>(durationUs)) + "µs"; // microseconds
    }
    else if(durationUs < 1000000) { 
        return std::to_string(static_cast<double>(durationUs) / 1000) + "ms"; // milliseconds
    }
    else {
        return std::to_string(static_cast<double>(durationUs) / 1000000) + "s"; // seconds
    } 
}

int main() {
    float* arr = new float[SIZE]{ };

    printf("Simulating single-threaded sorting numbers array size %s using MergeSort, please wait...\n",
            formatNumber(SIZE).c_str());

    printf("Initializing the array...\n", SIZE);
    auto start = std::chrono::high_resolution_clock::now(); // start benchmark
    populate(arr, SIZE);
    auto end = std::chrono::high_resolution_clock::now(); // stop
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("Array initialized successfully.\nTime took: %s\n", formatDuration(duration).c_str());
    
    printf("Sorting...\n");
    start = std::chrono::high_resolution_clock::now();
    sort(arr, SIZE);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("Numbers sorted successfully.\nTime took: %s\n", formatDuration(duration).c_str());


    delete[] arr;
    return 0;
}