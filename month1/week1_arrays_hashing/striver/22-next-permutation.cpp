// https://leetcode.com/problems/next-permutation/

#include<bits/stdc++.h>
using namespace std;
// Inside this algorithm we traverse from the 
// end and have an index variable indi which 
// take care of the index where the element is 
// less then its next element when we find that 
// index then break. if indi is -1 then no pivot 
// is found then reverse whole aray and return. 
// if indi is there then in that case travel from 
// the rightmost and find the element just greater 
// then indi index element and swap them and break. 
// After this reverse the array from 
// nums.begin() + indi + 1, nums.end()
// TC - O(n)+O(n)+O(n)=O(n)
// SC - O(1)

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int indi = -1;
        for(int i=nums.size()-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                indi = i;
                break;
            }
        }
        if(indi == -1){
            reverse(nums.begin(), nums.end());
            return;
        }
        for(int i = nums.size()-1; i > indi; i--) {
            if(nums[i] > nums[indi]) {
                swap(nums[i], nums[indi]);
                break;
            }
        }
        reverse(nums.begin() + indi + 1, nums.end());
        return;
    }
};


int main() {
    Solution obj;

    vector<int> nums = {2,1,5,4,3,0,0};

    obj.nextPermutation(nums);

    cout << "Next Permutation: ";
    for(int x : nums) {
        cout << x << " ";
    }

    return 0;
}