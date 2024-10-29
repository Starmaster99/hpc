#include <iostream>
#include <array>
#include <thread>
#include <fstream>

std::array<int, 1000> arr = {0};

void increment(int attempts) {
    for (int i = 0; i < attempts; i++) {
        int x = rand() % 1000;
        arr[x]++; 
    }
}

void decrement(int attempts) {
    for (int i = 0; i < attempts; i++) {
        int x = rand() % 1000;
        arr[x]--;
    }
}

int main() {
    srand(time(0));
    std::ofstream outFile("../simulation_results.csv");
    outFile << "array elements\n";

    int attempts = 100000;

    std::thread t1(increment, attempts);
    std::thread t2(decrement, attempts);

    // wait for threads to finish
    t1.join();
    t2.join();

    for(int i = 0; i <= arr.size(); i++) {
        outFile << arr[i] << std::endl;
    }

    outFile.close();
    return 0;
}