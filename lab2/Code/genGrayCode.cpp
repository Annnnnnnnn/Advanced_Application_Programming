#include "grayCode.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;



int main() {
    Solution sol;
    for (int i = 1; i <= 10; i++) {
        long int startTime, endTime;
        startTime = sol.getTime();
        string str = sol.grayCode(10);
        endTime = sol.getTime();
        std::cout << str << std::endl;
        cout<< "Round" << i << ": " <<  (float) (endTime-startTime)*1000/CLOCKS_PER_SEC << "ms" << endl;
    }
}
