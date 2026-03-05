// https://takeuforward.org/plus/dsa/problems/find-the-repeating-and-missing-number?subject=dsa&approach=optimal-ii&tab=editorial

#include<bits/stdc++.h>
using namespace std;

// Inside this we have first taken the xor of all elements
//  of the aray and the xor from 1 to n then after that we 
// find the right set bit with while(1){ if((xr & (1 << rightSet)) != 0) break; rightSet++; }; 
// then after fining that bit we divide the aray in two club, 
// sero club and one club take the take the xor of one club element 
// into one and zero club element into i. also did same thing for 
// the 1 to n. then after that check which is repeating and 
// missing and acordingly return answer.

// THere are other way also like by making two 
// equation and slving of sum of n natural no and 
// sum of sq of n natural no then find through it 

// one more way be can be by using unorderedMap

// TC - O(n)
// SC - O(1)

class Solution {
public:
    vector<int> findMissingRepeatingNumbers(vector<int> nums) {
        int xr = 0;
        int n = nums.size();
        for(int i=0;i<n;i++){
            xr = xr^nums[i];
            xr = xr^(i+1);
        }
        int rightSet = 0;
        while(1){
            if((xr & (1<<rightSet)) != 0) break;
            rightSet++;
        }
        int zero = 0,one = 0;
        for(int i=0;i<n;i++){
            if((nums[i] & (1<<rightSet)) !=0){
                one = one ^ nums[i];
            }else{
                zero = zero ^ nums[i]; 
            }
        }

        for(int i=0;i<n;i++){
            if(((i+1) & (1<<rightSet)) !=0){
                one = one ^ i+1;
            }else{
                zero = zero ^ i+1; 
            }
        }

        int cnt = 0; 

        for (int i = 0; i < n; i++) {
            if (nums[i] == zero) {
                cnt++;
            }
        }
        if (cnt == 2) {
            return {zero, one}; 
        }
        return {one, zero}; 
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
    vector<int> ans = obj.findMissingRepeatingNumbers(nums);

    cout << "Repeating: " << ans[0] << endl;
    cout << "Missing: " << ans[1] << endl;

    return 0;
}