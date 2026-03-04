#include <bits/stdc++.h>
using namespace std;

// firstly I have used created unordered map of the input
// array then in second loop i am checking for the required sum 
// TC - O(n) SC - O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for(int i = 0; i < nums.size(); i++){
            mp[nums[i]] = i; 
        }

        vector<int> ans;

        for(int i = 0; i < nums.size(); i++){
            int req = target - nums[i];
            auto it = mp.find(req);

            if(it == mp.end()){
                continue; 
            }
            else {
                if(it->second != i){
                    ans.push_back(i);
                    ans.push_back(it->second);
                    break;
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Test case
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = sol.twoSum(nums, target);

    cout << "Indices of elements summing to " << target << ": ";
    for(int idx : result){
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}