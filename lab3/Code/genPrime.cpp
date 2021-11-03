#include "findPrimes.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void singleThread(long number) {
    Solution sol;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
    cout << sol.findPrime(number) << endl;
}

int main() {
    singleThread(100);
}