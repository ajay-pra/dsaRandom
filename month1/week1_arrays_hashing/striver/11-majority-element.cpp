// https://leetcode.com/problems/majority-element/description/

// Given an array nums of size n, return the majority element.

// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.


#include<bits/stdc++.h>
using namespace std;

// inside this I have chosen the first element as the winner
// and started iterating over the elements 
// of the array i i got same element the 
// i increase counter and if other element 
// the decrese counter if counter is zero the 
// majority element will be that element only
// and update counter to 1 most of the time i do not update the counter to 1 while marking majority element in array

// TC - O(n)
// SC - O(1)
class Solution {
public:
int majorityElement(vector<int>& nums) {
    int maj = nums[0];
    int cnt = 1;
    for(int i=1;i<nums.size();i++){
        if(nums[i] == maj) {
            cnt++;
        } else {
            cnt--;
            if(cnt == 0) {
                maj = nums[i];
                cnt = 1;
            }
        }
    }
    return maj;
}

};

int main() {
    Solution sol;

    // Example test case
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    int result = sol.majorityElement(nums);
    
    cout << "The majority element is: " << result << endl;

    // Another test case
    vector<int> nums2 = {3, 3, 4};
    cout << "The majority element is: " << sol.majorityElement(nums2) << endl;

    return 0;
}