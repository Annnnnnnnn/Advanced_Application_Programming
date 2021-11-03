#include "findPrimes.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

Solution::Solution() {}

bool Solution::isprime(long num)
{
    long lim = num/2;
    if(num == 1)
    {
        return 0;
    }
    for(long i = 2; i <= lim; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
        else{ lim = num/i; }
    }
    return 1;
}
 
char* Solution::findPrime(long lim)
{
    vector<int> result;
    for(long i = 1; i <= lim || lim == 0; i++)
    {
        if(Solution::isprime(i)) {
            result.push_back(i);
        }
    }
    stringstream ss;
	string str;
	copy(result.begin(), result.end(), ostream_iterator<int>(ss, ","));
	str = ss.str();
    char *p=(char*)str.c_str();
    return p;
}
