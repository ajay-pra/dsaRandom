
// https://leetcode.com/problems/top-k-frequent-elements/

#include<bits/stdc++.h>
using namespace std;
//  inside this I have stored the frequency in unordered 
//  map and after that I put into vectorrs to sort it frequency
//  wiise then after that I have pushed top k elements
//  to a vector and returened them
//  TC - O(n) + O(nlogn) + O(k)
//  SC - O(n) + O(n)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        int n = nums.size()-1;
        for(int i=0;i<=n;i++){
            mp[nums[i]]++;
        }
        vector<pair<int,int>> pr(mp.begin(), mp.end());
        sort(pr.begin(), pr.end(), [](auto &a, auto &b){
            return a.second > b.second;
        });
        vector<int> ans;
        for(int i = 0; i < k; i++){
            ans.push_back(pr[i].first);
        }
        return ans;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;

    // Get top K frequent elements
    vector<int> result = sol.topKFrequent(nums, k);

    // Print the result
    cout << "Top " << k << " frequent elements are: ";
    for(int num : result){
        cout << num << " ";
    }
    cout << endl;

    return 0;
}