#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

// struct for some algorithm analysis statistics
struct Stats {
    u_long comparisons;    // comparisons number
    u_long acceses;        // array accesses number

    Stats() : comparisons(0), acceses(0) {} // initialize stats
};

void populate(float* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (static_cast<float>(rand()) / RAND_MAX) * 255.0f;
    }
}

void print(float* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

Stats sort(float* arr, int size) {
    Stats stats;    // an instance to track statistics
    // start from the second element since the first one has already been sorted
    // and iterate over until we reach the end of the array
    for (int i = 1; i < size; i++) {
        float current = arr[i]; // cache the current element to be inserted
        stats.acceses++;        // track array access
        int j = i - 1;          // counter for compairing the left part of the array
       
        // compare elements to the left
        // while there are elements to the left AND
        // while the element to the left is bigger than the current element
        // e.g. 8 and 4
        while (j >= 0 && arr[j] > current) {
            stats.comparisons += 2; // two comparisons above, not one
            stats.acceses++;
            // temporarily copy the element to the right to the left
            // e.g. 8 and 8 
            arr[j+1] = arr[j];
            stats.acceses++;
            // move the pointer backwards
            j--;
        }
        // and copy the cached element (4) to the left
        // e.g. 4 and 8
        arr[j+1] = current;
        stats.acceses++;
    }
    return stats;
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

std::string formatDuration(uint64_t durationUs) {
    if (durationUs < 10) {
        return "<0µs";
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

void runSimulation(int size) {
    float* arr = new float[size]{ };
    populate(arr, size);

    auto start = std::chrono::high_resolution_clock::now();
    Stats stats = sort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    printf("Simulation of size %s done in %s with %s comparisons.\n",
            formatNumber(size).c_str(),
            formatDuration(duration).c_str(),
            formatNumber(stats.comparisons).c_str());
    delete[] arr;
}

int main() {
    std::srand(std::time(0));

    int startSize = 2;
    int endSize = 500;

    printf("Simulating single-threaded sorting numbers using insertion sort, please wait...\n");
    for(int size = startSize; size <= endSize; size++) {
        runSimulation(size);
    }

    return 0;
}