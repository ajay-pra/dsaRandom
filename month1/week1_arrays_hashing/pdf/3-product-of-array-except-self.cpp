// https://leetcode.com/problems/product-of-array-except-self/submissions/1937613969/

#include<bits/stdc++.h>
using namespace std;

// firstly I have done prefix multiplication and suffix
//  multiplication and afte that iterate through the array 
// and calculated as directed in the question
// TC - O(n) + O(n) + O(n) 
// SC - O(n) + O(n)  + O(n)
// the below code is working but not fine 
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int prefixMulti[n];
        int suffixMulti[n];
        prefixMulti[0] = nums[0];
        suffixMulti[n-1] = nums[n-1];
        for(int i=1;i<=n-1;i++){
            prefixMulti[i] = prefixMulti[i-1] * nums[i];
        }
        for(int i=n-2;i>=0;i--){
            suffixMulti[i] = suffixMulti[i+1] * nums[i];
        }
        vector<int> ans;
        for(int i=0;i<n;i++){
            if(i==0) ans.push_back(suffixMulti[1]);
            else if(i==n-1) ans.push_back(prefixMulti[n-2]);
            else{
                ans.push_back(prefixMulti[i-1]*suffixMulti[i+1]);
            }
        }
        return ans;
    }
};


// here at the below is the more corect one in this we have not do lot of if and else

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixMulti(n), suffixMulti(n), ans(n);

        prefixMulti[0] = 1;
        for(int i=1; i<n; i++){
            prefixMulti[i] = prefixMulti[i-1] * nums[i-1];
        }

        suffixMulti[n-1] = 1;
        for(int i=n-2; i>=0; i--){
            suffixMulti[i] = suffixMulti[i+1] * nums[i+1];
        }

        for(int i=0; i<n; i++){
            ans[i] = prefixMulti[i] * suffixMulti[i];
        }

        return ans;
    }
};



int main(){
    Solution sol;
    vector<int> nums = {1,2,3,4};
    vector<int> ans = sol.productExceptSelf(nums);
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}