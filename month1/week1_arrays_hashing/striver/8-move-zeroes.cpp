// https://leetcode.com/problems/move-zeroes/description/

// Given an integer array nums, move all 0's to the end 
// of it while maintaining the relative order of the 
// non-zero elements.
// Note that you must do this in-place without making
// a copy of the array.

#include<bits/stdc++.h>
using namespace std;

// Firstly I haev taken a variable and initialize
//  it with zero and then itrated over the array,
//  checked if non zero then initialize nums[k] 
// to nums[i] after that remaining one are filled with 0
// TC - O(n)
// SC - O(1)
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int k = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i] != 0){
                nums[k] = nums[i];
                k++;
            }
        }
        for(int i=k;i<nums.size();i++){
            nums[i]=0;
        }
    }
};

// another aproach can be just swapping 

// class Solution {
// public:
//     void moveZeroes(vector<int>& nums) {
//         int j = 0;

//         for (int i = 0; i < nums.size(); i++) {
//             if (nums[i] != 0) {
//                 swap(nums[i], nums[j]);
//                 j++;
//             }
//         }
//     }
// };

int main() {
    Solution sol;

    // Test case
    vector<int> nums = {0, 1, 0, 3, 12};

    cout << "Original array: ";
    for(int num : nums) cout << num << " ";
    cout << endl;

    // Call moveZeroes
    sol.moveZeroes(nums);

    cout << "After moving zeroes: ";
    for(int num : nums) cout << num << " ";
    cout << endl;

    return 0;
}