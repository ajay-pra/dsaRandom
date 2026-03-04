// https://leetcode.com/problems/group-anagrams/

#include<bits/stdc++.h>
using namespace std;

// Inside this while iterating over the strings I created unique
// key for each array element and stored each element with that
// key, and after that mapping I have put in answer
// TC - O(n * k log k)
// SC - O(n * k)

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mp;
        for(int i=0;i<strs.size();i++){
            string key = strs[i];
            sort(key.begin(),key.end());
            mp[key].push_back(strs[i]);
        }
        auto it = &mp;
        vector<vector<string>> ans;
        for(auto &p:mp){
            ans.push_back(p.second);
        }
        // for(auto it = mp.begin(); it != mp.end(); ++it){
        //     ans.push_back(it->second);
        // }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> grouped = sol.groupAnagrams(strs);
    for(const auto &group : grouped) {
        cout << "[ ";
        for(const auto &s : group) {
            cout << s << " ";
        }
        cout << "]\n";
    }
    return 0;
}