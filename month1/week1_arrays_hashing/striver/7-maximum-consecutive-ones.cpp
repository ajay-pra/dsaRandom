// https://takeuforward.org/plus/dsa/problems/maximum-consecutive-ones?subject=dsa

#include<bits/stdc++.h>
using namespace std;
// I have iterated over the array and whenever i get 
// 1 then i have increased count and whenever 0
//  then reset count to zero and before that
//  i calculated maxCount
// TC - O(n)
// SC - O(1)
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int count = 0;
        int maxCount = INT_MIN;
        for(int i=0;i<nums.size();i++){
            if(nums[i] == 1) count++;
            else{
                maxCount = max(maxCount, count);
                count = 0;
            }
        }
        maxCount = max(maxCount, count);
        return maxCount;
    }
};


int main() {
    Solution sol;

    // Example 1
    vector<int> nums1 = {1, 1, 0, 1, 1, 1};
    cout << "Max consecutive ones in nums1: " << sol.findMaxConsecutiveOnes(nums1) << endl;

    // Example 2
    vector<int> nums2 = {0, 0, 0, 0};
    cout << "Max consecutive ones in nums2: " << sol.findMaxConsecutiveOnes(nums2) << endl;

    // Example 3
    vector<int> nums3 = {1, 1, 1, 1, 1};
    cout << "Max consecutive ones in nums3: " << sol.findMaxConsecutiveOnes(nums3) << endl;

    return 0;
}