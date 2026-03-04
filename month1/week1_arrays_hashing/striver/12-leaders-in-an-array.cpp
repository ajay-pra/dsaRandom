// https://takeuforward.org/plus/dsa/problems/leaders-in-an-array?subject=dsa

// Given an integer array nums, return a list of all the leaders in the array.

// A leader in an array is an element whose value is strictly greater than all elements to its right in the given array. The rightmost element is always a leader. The elements in the leader array must appear in the order they appear in the nums array.

#include<bits/stdc++.h>
using namespace std;
// inside this I strted from back nd I haaave chosen
//   mjor element nd based on that i 
// compre ech index element if any greater 
// i got then i update my max and push in ans
// TC - O(n)+O(n)=O(n)
// SC - O(n)

class Solution {
public:
    vector<int> leaders(vector<int>& nums) {
      int n = nums.size()-1;
      int maxx = nums[n];
      vector<int> ans;
      ans.push_back(maxx);
      for(int i = n-1;i>=0;i--){
        if(nums[i]>maxx){
            maxx = nums[i];
            ans.push_back(maxx);
        }
      }
      reverse(ans.begin(), ans.end());
      return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {16, 17, 4, 3, 5, 2};

    vector<int> result = sol.leaders(nums);

    cout << "Leaders in the array: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}