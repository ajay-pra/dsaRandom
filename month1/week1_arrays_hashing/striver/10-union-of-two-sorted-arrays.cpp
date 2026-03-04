// https://takeuforward.org/plus/dsa/problems/union-of-two-sorted-arrays?subject=dsa

// Given two sorted arrays nums1 and nums2, return an array that contains the union of these two arrays. The elements in the union must be in ascending order.
// The union of two arrays is an array where all values are distinct and are present in either the first array, the second array, or both.

// https://takeuforward.org/plus/dsa/problems/union-of-two-sorted-arrays?subject=dsa&tab=submissions

#include<bits/stdc++.h>
using namespace std;


// inside this I have takend two pointers i and j and run
// them till size of nums1 and nums2 also used a flag 
// variable pushed to check wi=hich number is pushed 
// latest in array, as the aray is already sorted 
// so no need of sorting is required. checked eache 
// element of two arays and pushed in ans array accordingly
//  and updated the pushed aray also 

// TC - O(s1+s2)
// SC - O(s1+s2)

class Solution {
public:
    vector<int> unionArray(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        int pushed = INT_MIN;
        int i=0,j=0;
        while(i<nums1.size() && j<nums2.size()){
            if(nums1[i]<nums2[j] && pushed!= nums1[i]){
                ans.push_back(nums1[i]);
                pushed = nums1[i];
                i++;
            }else if(nums2[j]<nums1[i] && pushed!= nums2[j]){
                ans.push_back(nums2[j]);
                pushed = nums2[j];
                j++;
            }else{
                if(pushed != nums1[i]){
                    ans.push_back(nums1[i]);
                    pushed = nums1[i];
                    i++;j++;
                }
            }
        }
        while(i<nums1.size()){
                if(pushed!= nums1[i]){
                    ans.push_back(nums1[i]);
                    pushed = nums1[i];
                }
                i++;
            }
            while(j<nums2.size()){
                if(pushed!= nums2[j]){
                    ans.push_back(nums2[j]);
                    pushed = nums2[j];
                }
                j++;
            }
        return ans;
    }
};


int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 4, 5};
    vector<int> nums2 = {2, 3, 5, 6};

    vector<int> result = sol.unionArray(nums1, nums2);

    cout << "Union of arrays: ";
    for(int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}