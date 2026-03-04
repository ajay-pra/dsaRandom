<!-- way to iterate over mp -->
for(auto it = mp.begin(); it != mp.end(); ++it){
    ans.push_back(it->second);
}
for(auto &p : mp){
    ans.push_back(p.second);
}

<!-- Pair sorting -->
vector<pair<int,int>> pr(mp.begin(), mp.end());
sort(pr.begin(), pr.end(), [](auto &a, auto &b){
    return a.second > b.second;
});

<!-- wy to iterte over set -->
for (int val : s) { 
    nums[i++] = val; 
}

<!-- reverse n vector -->
reverse(ans.begin(), ans.end());