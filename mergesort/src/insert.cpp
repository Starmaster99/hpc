#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <fstream>

// struct for some algorithm analysis statistics
struct Stats {
    unsigned comparisons;    // comparisons number
    unsigned acceses;        // array accesses number
    double a;              // current amount comparisons to the total amount of pairs to compare

    Stats() : comparisons(0), acceses(0), a(0.0) {} // initialize stats
};

void populate(float* arr, int size, int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 255.0);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

Stats sort(float* arr, int size) {
    Stats stats;

    for (int i = 1; i < size; i++) {
        float current = arr[i];
        stats.acceses++;
        int j = i - 1; 

        while (j >= 0 && arr[j] > current) {
            stats.comparisons++;
            stats.acceses++;
            arr[j+1] = arr[j];
            stats.acceses++;
            j--;
        }
        arr[j+1] = current;
        stats.acceses++;
    }
    stats.a = static_cast<double>(stats.comparisons) / ((size * (size - 1) / 2)); 

    return stats;
}

std::string formatNumber(uint64_t num) {
    std::stringstream ss;
    ss.imbue(std::locale("en_US.UTF-8"));   // regional thing. en_US.UTF-8 for commas
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

Stats runSimulation(float* arr, int size, int seed) {
    populate(arr, size, seed);

    auto start = std::chrono::high_resolution_clock::now();
    Stats stats = sort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return stats;
}

int main() {
    int startSize = 3;
    int endSize = 50;
    int simulations = 50;
    int seed = std::random_device{}();
    float* arr = new float[endSize]{ };

    printf("Simulating single-threaded sorting numbers using insertion sort, please wait...\n");

    std::ofstream outFile("../simulation_results_insert.csv");

    outFile << "Size,Simulations,Average a\n";

    for(int size = startSize; size <= endSize; size++) {
        double totalA = 0.0;

        // run simulation for 50 times for each array with current size and get
        // the average a
        for(int i = 0; i <= simulations; i++) {
            Stats stats = runSimulation(arr, size, seed);
            totalA += stats.a;
        }
        double averageA = totalA / simulations;
        printf("Average 'a' for size %d after %d simulations: %.5f\n", size, simulations, averageA);
        outFile << size << "," << simulations << "," << averageA << "\n";
    }

    outFile.close();
    delete[] arr;
    return 0;
}