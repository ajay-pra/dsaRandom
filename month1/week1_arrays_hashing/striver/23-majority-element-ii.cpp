// https://leetcode.com/problems/majority-element-ii/

#include<bits/stdc++.h>
using namespace std;

// Inside this we have used same algorithm as the 
// majorityelement1 but here we are taking two 
// counter and two element, there is an additional 
// check in this the element we fill find after 
// running the algo will will again find the count 
// of them in the nums and if it is greater then 
// n/3 then we will push that element in the array
// TC - O(n) + O(n)
// SC - O(1)

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int ele1=INT_MIN,ele2=INT_MIN,cnt1=0,cnt2=0;
        for(int i=0;i<nums.size();i++){
            if(cnt1 == 0 && ele2 != nums[i]){
                ele1=nums[i];
                cnt1=1;
            }else if(cnt2 == 0 && ele1 != nums[i]){
                ele2 = nums[i];
                cnt2 = 1;
            }else if(nums[i] == ele1) {
                cnt1++;
            }else if(nums[i] == ele2) {
                cnt2++;
            }else{
                cnt1--;
                cnt2--;
            }
        }
         cnt1 = 0, cnt2 = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i] == ele1) cnt1++;
            if(nums[i] == ele2) cnt2++;
        }

        vector<int> ans;
        int n = nums.size();
        if(cnt1 > n/3) ans.push_back(ele1);
        if(cnt2 > n/3) ans.push_back(ele2);
        return ans;
    }
};


int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }

    Solution obj;
    vector<int> result = obj.majorityElement(nums);

    for(int x : result){
        cout << x << " ";
    }

    return 0;
}