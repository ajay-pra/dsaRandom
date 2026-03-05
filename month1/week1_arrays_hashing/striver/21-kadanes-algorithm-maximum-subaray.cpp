// https://leetcode.com/problems/maximum-subarray/submissions/1938556216/

#include<bits/stdc++.h>
using namespace std;

// Inside this I have used kadans algorithm in 
// this we take two variable sum and
//  max sum (initilize it with INT_MIN)
//  and the iterate over the array and
//  update the sum sum+=nums[i], 
// then checked the sum value of 
// it with maxSum if it is greater
//  then update max sum and if sum<0
//  then make sum to zero;

// TC - O(n)
// SC - O(1)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int maxSum = INT_MIN;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            if(sum>maxSum){
                maxSum = sum;
            }
            if(sum<0) {
                sum = 0;
            }
        }
        return maxSum;
    }
};


// If there is a need to return the index also 
class Solution {
public:
    vector<int> maxSubArray(vector<int>& nums) {
        int sum = 0;
        int maxSum = INT_MIN;

        int start = 0, ansStart = 0, ansEnd = 0;

        for(int i = 0; i < nums.size(); i++){
            if(sum == 0) start = i;
            sum += nums[i];
            if(sum > maxSum){
                maxSum = sum;
                ansStart = start;
                ansEnd = i;
            }
            if(sum < 0) sum = 0;
        }

        vector<int> result;
        for(int i = ansStart; i <= ansEnd; i++){
            result.push_back(nums[i]);
        }

        return result;
    }
};



int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    Solution obj;
    int result = obj.maxSubArray(nums);
    cout << result;
    return 0;
}