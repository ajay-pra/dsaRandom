#include<bits/stdc++.h>
using namespace std;

// I have used a unordered map and store each index
//  and while iterating only I am checking if the the
//  data is existing and if it exist then break and
//  make ans false 
// TC - O(n), SC - O(n)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mp;
        bool ans = false;
        for(int i=0;i<nums.size();i++){
            if(mp.find(nums[i])!= mp.end()){
                ans = true;
                break;
            }
            mp[nums[i]] = i;
        }
        return ans;
    }
};


int main(){
    Solution sol;
    vector<int> nums = {1,2,3,0};
    bool ans = sol.containsDuplicate(nums);
    cout<<"Ans is:" << ans;
    return 0;
}