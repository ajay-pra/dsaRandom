// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/

// Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same.

// Consider the number of unique elements in nums to be k​​​​​​​​​​​​​​. After removing duplicates, return the number of unique elements k.

// The first k elements of nums should contain the unique numbers in sorted order. The remaining elements beyond index k - 1 can be ignored.


#include<bits/stdc++.h>
using namespace std;

// inside this I have used a map to store set to
// store all unique values and updated the array
// with set and returns set size
// TC - O(n)
// SC - O(1)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        set<int> s;
        for(int i=0;i<nums.size();i++){
            s.insert(nums[i]);
        }
        int i = 0;
        for (int val : s) { 
            nums[i++] = val; 
        }
        return s.size();
    }
};

// another way could be without using any STL,
//  inside this I have iniitlize a variable k
//  with 1 and pushed started my array with
//  index 1 and checked the curent value
//  with previous if not equal then do
//  nums[k] = nums[i] and k++

// class Solution {
// public:
//     int removeDuplicates(vector<int>& nums) {
//         int k=1;
//         for(int i=1;i<nums.size();i++){
//             if(nums[i]!=nums[i-1]){
//                 nums[k] = nums[i];
//                 k++;
//             }
//         }
//         return k;
//     }
// };



int main() {
    Solution sol;

    vector<int> nums = {1, 1, 2, 2, 3, 4, 4, 5};

    int newLength = sol.removeDuplicates(nums);

    cout << "Length after removing duplicates: " << newLength << endl;
    cout << "Array after removing duplicates: ";
    for(int i = 0; i < newLength; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}