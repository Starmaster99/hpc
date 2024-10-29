#include <iostream>
#include <thread>
#include <string>
#include <random>
#include <chrono>

// these are global variables, i.e. shared by each thread
int addressee = 0;
std::string message = "Hey! How's your day going?";

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> sleep_dist(10, 30);
std::uniform_int_distribution<> id_dist(0, 5);      // select thread randomly

void threadF(int id) {
    // no one told when to stop
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen))); // random sleep

        if (addressee == id) {  // check if it's this thread's turn
            // print the current message and thread ID
            std::cout << "Thread " << id << " received message: " << message << std::endl;

            // update the message and addressee
            message = "Hello from thread " + std::to_string(id);
            addressee = id_dist(gen); // set a new random addressee
        }
    }
}

int main() {
    const int numThreads = 6;
    std::thread threads[numThreads];

    // launch threads with unique IDs
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(threadF, i);
    }

    // join threads to main thread
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    return 0;
}
