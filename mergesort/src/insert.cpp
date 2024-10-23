#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>

// struct for some algorithm analysis statistics
struct Stats {
    u_long comparisons;    // comparisons number
    u_long acceses;        // array accesses number

    Stats() : comparisons(0), acceses(0) {} // initialize stats
};

void populate(float* arr, int size) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis(0.0, 255.0);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
}
}

Stats sort(float* arr, int size) {
    Stats stats;    // an instance to track statistics  
    // start from the second element since the first one has already been sorted
    // and iterate over until we reach the end of the   array
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
    std::stringstream ss;
    ss.imbue(std::locale(""));   // regional thing. en_US.UTF-8 for commas
    ss << num;
    return ss.str();
}

std::string formatDuration(uint64_t durationUs) {
    std::ostringstream oss;

    if (durationUs < 10) {
        return "<0µs";
    }
    else if(durationUs < 1000) {
        oss << durationUs << "µs"; // microseconds
    }
    else if(durationUs < 1000000) { 
        oss << std::fixed << std::setprecision(2) << static_cast<double>(durationUs) / 1000 << "ms"; // milliseconds
    }
    else {
         oss << std::fixed << std::setprecision(2) << static_cast<double>(durationUs) / 1000000 << "s"; // seconds
    } 
    return oss.str();
}

void runSimulation(float* arr, int size) {
    populate(arr, size);

    auto start = std::chrono::high_resolution_clock::now();
    Stats stats = sort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    printf("Simulation of size %s done in %s with %s comparisons.\n",
            formatNumber(size).c_str(),
            formatDuration(duration).c_str(),
            formatNumber(stats.comparisons).c_str());
}

int main() {
    std::srand(std::time(0));

    int startSize = 1;
    int endSize = 500;
    float* arr = new float[endSize]{ };

    printf("Simulating single-threaded sorting numbers using insertion sort, please wait...\n");
    for(int size = startSize; size <= endSize; size++) {
        runSimulation(arr, size);
    }

    delete[] arr;
    return 0;
}