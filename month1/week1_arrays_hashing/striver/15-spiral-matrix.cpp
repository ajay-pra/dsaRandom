// https://leetcode.com/problems/spiral-matrix/

#include<bits/stdc++.h>
using namespace std;

// inside this I have used four variable left, right, top, bottom 
// which are initialized according to the size of 
// the matrix then i traverse from left to right 
// and then top-- and the top to bottom then right-- 
// and then right to left(only when top<=bottom) 
// and bottom-- and then bottom to up(only when left <= right)
//  then left ++, everythign will be in loop till left<=right
//  and top<=bottom
// TC - O(m*n)
// SC - O(m*n)


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> ans;
        int left=0,right=n-1,top=0,bottom=m-1;
        while(left<=right && top<=bottom){
            for(int i=left;i<=right;i++){
                ans.push_back(matrix[top][i]);
            }
            top++;
            for(int i=top;i<=bottom;i++){
                ans.push_back(matrix[i][right]);
            }
            right--;
             if (top <= bottom) {
                for (int i = right; i >= left; i--) {
                    ans.push_back(matrix[bottom][i]);
                }
                bottom--;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    ans.push_back(matrix[i][left]);
                }
                left++;
            }          
        }
        return ans;
    }
};


int main() {
    Solution sol;

    // Example 2D matrix
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> result = sol.spiralOrder(matrix);

    cout << "Spiral Order: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}