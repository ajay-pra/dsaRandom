// https://leetcode.com/problems/pascals-triangle-ii/submissions/1938455868/

#include<bits/stdc++.h>
using namespace std;

//  this uses same concept as previous pascal
//  triangle one here we are storing each element
//  while multiplication
// TC - O(rowIndex)
// SC - O(rowIndex)

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans;
        int res = 1;
        for(int i = 0; i <= rowIndex; i++) {
            ans.push_back(res);
            res = res * (rowIndex - i) / (i + 1); 
        }
        return ans;
    }
};


int main() {
    Solution sol;
    int rowIndex = 3;
    vector<int> row = sol.getRow(rowIndex);

    for(int num : row) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
