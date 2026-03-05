// https://leetcode.com/problems/pascals-triangle/description/

#include<bits/stdc++.h>
using namespace std;

// inside this the nth row and rth column 
// in a pascal triangle is nCr (both are zero indexed), 
// but we can not calculate the factorial of 
// the numbers it might cause integer overflow 
// so we have done this to go iteratively 
// from i = 0 to k then in the loop do ans = (ans * (n - i)) / (i + 1);

// TC - O(k)
// SC - O(1)
class Solution {
public:
    int pascalTriangleI(int r, int c) {
        int n = r-1;
        int k = c-1;
        int ans = 1;
        for(int i=0;i<k;i++){
            ans = (ans * (n-i)/(i+1));
        }
        return ans;
    }
};

int main() {
    Solution sol;

    // Hardcoded row and column
    int row = 5;
    int col = 3;

    int value = sol.pascalTriangleI(row, col);
    cout << "The value at row " << row << " and column " << col 
         << " in Pascal's Triangle is: " << value << endl;

    return 0;
}