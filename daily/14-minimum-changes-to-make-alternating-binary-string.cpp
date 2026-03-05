// https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/submissions/1938408363/?envType=daily-question&envId=2026-03-05

class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int count1 = 0, count2 = 0;

        for(int i = 0; i < n; i++){
            if(s[i] != (i % 2 == 0 ? '0' : '1')) count1++;
            if(s[i] != (i % 2 == 0 ? '1' : '0')) count2++;
        }
        return min(count1, count2);
    }
};