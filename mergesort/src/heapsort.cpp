#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cmath>

std::ofstream outFile("../simulation_results_merge.csv");

void populate(float* arr, int size, int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 255.0);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

void heapify(float* arr, int n, int i, unsigned& comparisons) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    // Iterative heapify
    while (true) {
        int currentLargest = largest;

        // Check if left child exists and is larger than root
        if (left < n) {
            comparisons++;
            if (arr[left] > arr[currentLargest]) {
                currentLargest = left;
            }
        }

        // Check if right child exists and is larger than the current largest
        if (right < n) {
            comparisons++;
            if (arr[right] > arr[currentLargest]) {
                currentLargest = right;
            }
        }

        // If the largest is still the root, break
        if (currentLargest == largest) {
            break;
        }

        // Otherwise, swap and continue heapifying
        std::swap(arr[largest], arr[currentLargest]);
        largest = currentLargest;
        left = 2 * largest + 1;
        right = 2 * largest + 2;
    }
}

void heapsort(float* arr, int n, unsigned& comparisons, double& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    // Step 1: Build the max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons);
    }

    // Step 2: Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // Reduce the heap and maintain max-heap property
        heapify(arr, i, 0, comparisons);
    }

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double, std::milli>(end - start).count();
}


void runSimulation(float* arr, int iterations, int arraySize, int seed) {
    double totalComparisons = 0.0;
    double totalTime = 0.0;

    for (int i = 0; i < iterations; i++) {
        populate(arr, arraySize, seed);

        unsigned comparisons = 0;
        double duration = 0.0;

        heapsort(arr, arraySize, comparisons, duration);

        totalComparisons += comparisons;
        totalTime += duration;
    }

    double averageComparisons = totalComparisons / iterations;
    double averageTime = totalTime / iterations;
    double a = averageComparisons / (arraySize * std::log2(arraySize));

    outFile << arraySize << "," << iterations << "," << averageTime << "," << a << "\n";
    printf("Size: %i\nAverage comparisons: %f\nAverage time (ms): %f\nAverage 'a': %f\n", 
            arraySize, averageComparisons, averageTime, a);
}

int main() {
    int startSize = 3;
    int endSize = 50;
    int iterations = 50;
    int seed = std::random_device{}();
    float* arr = new float[endSize];

    outFile << "Size,Iterations,Average Time (ms),Average A\n";

    for (int size = startSize; size <= endSize; size++) {
        runSimulation(arr, iterations, size, seed);
    }

    delete[] arr;
    return 0;
}
