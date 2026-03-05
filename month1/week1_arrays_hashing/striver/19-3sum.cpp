// https://leetcode.com/problems/3sum/submissions/1938514856/

#include<bits/stdc++.h>
using namespace std;

// inside this I am using two pointer approach to
//  solve this it will work on sorted array only,
//  I have sort the array and started a loop from
//  i=0 to n-1 and inside that loop i have taken
//  left = i+1 and right = n-1 and run another
//  while loop in which i am comparing if the
//  nums[left] + nums[right] == -nums[i]; 
// and update left and right according to
//  equal less or greater. One most important
//  thing that as we need to avoide duplicate
//  then at each step we have to check if 
// I am not taking any duplicate that i have 
// checked with wile loop 

// TC - O(nlogn)+O(n
// SC - O(n) - for ans
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i=0;i<n;i++){
            if(i>0 && nums[i] == nums[i-1]) continue;
            int left = i+1,right = n-1;
            while(left<right){
                int target = -nums[i];
                if(nums[left]+nums[right] == target){
                    vector<int> temp = {nums[i],nums[left],nums[right]};
                    ans.push_back(temp);
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }else if(nums[left]+nums[right]<target){
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                }else{
                    right --;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
            }
        }
        return ans;
    }
};



int main() {

    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    Solution obj;
    vector<vector<int>> result = obj.threeSum(nums);
    cout << "Triplets with sum = 0:\n";
    for(auto &triplet : result){
        for(int num : triplet){
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}