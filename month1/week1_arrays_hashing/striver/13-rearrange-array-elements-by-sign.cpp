// https://leetcode.com/problems/rearrange-array-elements-by-sign/description/

#include<bits/stdc++.h>
using namespace std;
// inside this I have tken two vribles pos nd neg 
// and started iterating over the array if 
// i find any positive or negative vlue then 
// acordingly updte the answer and update the indexes
// TC - O(n)
// SC - O(n)
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int pos = 0, neg = 1;
        vector<int> ans(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                ans[pos] = nums[i];
                pos += 2;
            } else {
                ans[neg] = nums[i];
                neg += 2;
            }
        }
        return ans;
    }
};


int main() {
    Solution sol;

    vector<int> nums = {3, 1, -2, -5, 2, -4};
    
    vector<int> rearranged = sol.rearrangeArray(nums);
    
    cout << "Rearranged array: ";
    for (int num : rearranged) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}