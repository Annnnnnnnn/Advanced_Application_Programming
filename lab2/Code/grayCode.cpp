#include "grayCode.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

Solution::Solution() {}

long int Solution::getTime() {
    return clock();
}

char* Solution::grayCode(int n) {
    vector<int> result;
    result.push_back(0);
    
    for (int i = 1; i <= n; i++) {
        int previousSequenceLength = result.size();
        int mask = 1 << (i - 1);
        for (int j = previousSequenceLength - 1; j >= 0; j--) {
            result.push_back(mask + result[j]);
        }
    }
    // for(vector<int>::iterator i = result.begin(); i != result.end(); ++i) {
    //     cout<< *i << endl; 
    // 
    stringstream ss;
	string str;
	copy(result.begin(), result.end(), ostream_iterator<int>(ss, ","));
	str = ss.str();
    char *p=(char*)str.c_str();
    cout << p << endl;
    return p;
}

// vector<int> grayCodeInOneloop(int n) {
//     vector<int> result;
//     // there are 2 ^ n numbers in the Gray code sequence.
//     int sequenceLength = 1 << n;
//     for (int i = 0; i < sequenceLength; i++) {
//         int num = i ^ i >> 1;
//         result.push_back(num);
//     }
//     return result;
// }