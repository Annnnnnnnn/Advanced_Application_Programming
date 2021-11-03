#include <vector>
#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <mutex>
#include <functional>
#include <iterator>

using namespace std;

bool isprime(long num)
{
    long lim = num/2;
    if(num == 1) {
        return 0;
    }
    for(long i = 2; i <= lim; i++) {
        if (num % i == 0) {
            return 0;
        }
        else { lim = num/i; }
    }
    return 1;
}

void * findPrime(long start, vector<string> &result)
{
    vector<int> partOfResult;
    for(long i = start; i<=1000000; i += 4)
    {
        if(isprime(i)) {
            partOfResult.push_back(i);
        }
    }
    stringstream ss;
	string str;
	copy(partOfResult.begin(), partOfResult.end(), ostream_iterator<int>(ss, ","));
	str = ss.str();
    char *ptr=(char*)str.c_str();
    mutex mtx;
    mtx.lock();
    result.push_back(ptr);
    mtx.unlock();
    return ptr;
}

int main() {
    vector<thread> threads;
    vector<string> result;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 4; i++) {
        threads.push_back(thread(findPrime, i, ref(result)));
    }
    for (auto &th : threads) {
        th.join();
    }
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << " ms\n";
    // for (int i=0; i<result.size(); i++)
    //    cout << result[i] << " ";
    return 0;
}