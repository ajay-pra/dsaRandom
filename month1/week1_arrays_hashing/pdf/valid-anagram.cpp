// https://leetcode.com/problems/valid-anagram/submissions/1937656215/

#include<bits/stdc++.h>
using namespace std;

// i have used two unordered map and in each map
//  i am storing the frequesncy of letters of 
// string in mp respectively and aftr that
//  I am compering the frequency map
// TC - O(n) + O(26)
// SC - O(n) + O(n)

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char,int> mp1, mp2;
        bool ans = true;
        if(s.length() != t.length()) {
            ans = false;
            return ans;
        }
        int n = s.length()-1;
        for(int i=0;i<n;i++){
            mp1[s[i]-'a']++;
            mp2[t[i]-'a']++;
        }
        for(int i=0;i<26;i++){
            if(mp1[i] != mp2[i]) {
                ans = false;
                break;
            }
        }
        return ans;
    }
};


int main() {
    Solution sol;
    string  s1 = "anagram", s2 = "nagaram";

    if(sol.isAnagram(s1, s2))
        cout << "Strings are anagrams" << endl;
    else
        cout << "Strings are not anagrams" << endl;

    return 0;
}