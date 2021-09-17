#include <iostream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        const int n = s.length();
        
        vector<vector<int> > dp(n, vector<int>(n, 0));
		// dp[i][j] = length of longest palindrome subseq in s[i:j]
        vector<vector<char> > edge(n, vector<char>(n));
        // edge[i][j] = edge of longest palindrome subseq in s[i:j]
		
        for(int len = 2; len <= n; ++len) {
            for(int l = 0, r = len - 1; r < n; ++l, ++r) {
				// s[l] != edge[l + 1][r - 1]  ->  Exclude the case of two consecutive characters
				// len == 2  ->  Except the two middle ones
                if(s[l] == s[r] && (len == 2 || s[l] != edge[l + 1][r - 1])) {
                    dp[l][r] = 2 + dp[l + 1][r - 1];
                    edge[l][r] = s[l];
                }
                else if(dp[l][r - 1] > dp[l + 1][r]) {
                    dp[l][r] = dp[l][r - 1];
                    edge[l][r] = edge[l][r - 1];
                }
                else {
                    dp[l][r] = dp[l + 1][r];
                    edge[l][r] = edge[l + 1][r];
                }
            }
        }
        
        return dp[0][n - 1];
    }
};

int main() {
	string s = "dijjrxupqsicmtyaasuunajarjsmvyxnnlhwnvctehrprrkedfzjmjtgkbprlhskyadszukxfbbikuyjacjhupngrewdvcspzychhhokkaueazarzydrgavzqgsxbxbvsxwqikdijjrxupqsicmtyaasuunajarjsmvyxnnlhwnvctehrprrkedfzjmjtgkbprlhskyadszukxfbbikuyjacjhupngrewdvcspzychhhokkaueazarzydrgavzqgsxbxbvsxwqikdijjrxupqsicmtyaasuunajarjsmvyxnnlhwnvctehrprrkedfzjmjtgkbprlhskyadszukxfbbikuyjacjhupngrewdvcspzychhhokkaueazarzydrgavzqgsxbxbvsxwqikdijjrxupqsicmtyaasuunajarjsmvyxnnlhwnvctehrprrkedfzjmjtgkbprlhskyadszukxfbbikuyjacjhupngrewdvcspzychhhokkaueazarzydrgavzqgsxbxbvsxwqikdijjrxupqsicmtyaasuunajarjsmvyxnnlhwnvctehrprrkedfzjmjtgkbprlhskyadszukxfbbikuyjacjhupngrewdvcspzychhhokkaueazarzydrgavzqgsxbxbvsxwqikdijjrxupqsicmtyaasuunajarjsmvyxnnlhwnvctehrprrkedfzjmjtgkbprlhskyadszukxfbbikuyjacjhupngrewdvcspzychhhokkaueazarzydrgavzqgsxbxbvsxwqik";
	for(int i = 1; i <= 20; i = i + 1) {
        clock_t start, end;
        start = clock();
        Solution ans;
        int ret;
        ret = ans.longestPalindromeSubseq(s);
        end = clock();
        cout << "This is the " << i << " calculation" << endl;
        cout << ret << endl;
        cout << "Start time: " << start << endl;
        cout << "End time: " << end << endl;
        cout << "Total time: " << (double)(end - start)/CLOCKS_PER_SEC << end;
        cout << "\n" << endl;
    }

	return 0;
}
