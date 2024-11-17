#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>

unsigned comparisons = 0;
double a = 0.0f;
std::ofstream outFile("../simulation_results_merge.csv");

void populate(float* arr, int size, int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 255.0);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

void merge(float* left, float* right, float* arr, int size) {
    int leftSize = size / 2;
    int rightSize = size - leftSize;

    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        comparisons++; // Increment comparison counter
        if (left[l] < right[r]) {
            arr[i++] = left[l++];
        } else {
            arr[i++] = right[r++];
        }
    }

    while (l < leftSize) {
        arr[i++] = left[l++];
    }
    while (r < rightSize) {
        arr[i++] = right[r++];
    }
}

void sort(float* arr, int size) {
    if (size <= 1) return;
    int middle = size / 2;

    float* left  = new float[middle]{ };
    float* right = new float[size - middle]{ };

    for (int i = 0; i < middle; i++) {
        left[i] = arr[i];
    }
    for (int i = 0; i < size - middle; i++) {
        right[i] = arr[middle + i];
    }

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
        // microseconds
        return std::to_string(static_cast<double>(durationUs)) + "µs"; 
    }
    else if(durationUs < 1000000) { 
        // milliseconds
        return std::to_string(static_cast<double>(durationUs) / 1000) + "ms";
    }
    else {
        // seconds
        return std::to_string(static_cast<double>(durationUs) / 1000000) + "s";
    } 
}

void runSimulation(float* arr, int iterations, int arraySize, int seed) {
    double totalComparisons = 0.0;
    double totalA = 0.0;

    for (int i = 0; i < iterations; i++) {

        populate(arr, arraySize, seed);

        comparisons = 0;
        sort(arr, arraySize);

        a = static_cast<double>(comparisons) / ((arraySize * (arraySize - 1)) / 2);

        totalComparisons += comparisons;
        totalA += a;
    }

    double averageComparisons = totalComparisons / iterations;
    double averageA = totalA / iterations;

    outFile << arraySize << "," << iterations << "," << averageA << "\n";
    printf("Size: %i\nAverage comparisons: %f\nAverage 'a': %f\n", 
            arraySize, averageComparisons, averageA);
}

int main() {
    int startSize = 3;
    int endSize = 50;
    int iterations = 5000;
    int seed = std::random_device{}();
    float* arr = new float[endSize]{ };

    outFile << "Size,Iterations,Average A\n";

    for(int size = startSize; size <= endSize; size++) {
        runSimulation(arr, iterations, size, seed);
    }

    delete[] arr;
    return 0;
}