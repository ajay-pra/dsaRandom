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

// ANother optimized way can be removing the extra space 
// which we are using for ans, we can remove the requirement 
// of that extra space and have two pointer pos and negative 
// and run while loop till pos and neg are less then n, 
// and inside the loop i will find first pos and first neg index 
// and if the indexes are withing range then swap those two
// TC - O(n)
// SC - O(1)

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        int pos = 0; 
        int neg = 1; 

        while (pos < n && neg < n) {
            // find positive at wrong place
            while (pos < n && nums[pos] > 0) pos += 2;
            // find negative at wrong place
            while (neg < n && nums[neg] < 0) neg += 2;

            // swap only if both pointers are within array
            if (pos < n && neg < n) swap(nums[pos], nums[neg]);
        }

        return nums;
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