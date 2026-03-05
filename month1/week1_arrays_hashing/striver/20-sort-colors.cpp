// https://leetcode.com/problems/sort-colors/description/


#include<bits/stdc++.h>
using namespace std;

// THis is basically douch national flag algorithm
//  in this we divide the array in low mid and high
//  zones i.e from low to mid-1, mid to high-1,
//  hight to n-1 and acording to nums[mid]
//  we chenge the position of elements in the array.
// TC - O(n)
// SC - O(1)

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low=0, mid=0, high=nums.size()-1;;
        while(mid<=high){
            if(nums[mid] == 0){
                swap(nums[low],nums[mid]);
                low++;
                mid++;
            }else if(nums[mid] == 1){
                mid++;
            }else{
                swap(nums[high],nums[mid]);
                high--;
            }
        }
    }
};


int main() {

    vector<int> nums = {2, 0, 2, 1, 1, 0};

    Solution obj;
    obj.sortColors(nums);

    for(int x : nums){
        cout << x << " ";
    }

    return 0;
}