# 🧠 HASHING — Quick Revision Notes (C++ STL)

Hashing = Technique to **store & access data in O(1) average time**
Uses **Hash Table** internally.

Used in:

* Frequency counting
* Duplicate detection
* Fast lookup problems
* Two Sum / Subarray problems
* Caching

---

# 🔹 1️⃣ `unordered_map` (HashMap)

```cpp
#include <unordered_map>
unordered_map<int,int> mp;
```

👉 Stores **Key → Value**
👉 Order NOT guaranteed
👉 Average Time: **O(1)**

---

## ✅ Insert / Update

```cpp
mp[key] = value;        // Insert OR update
mp.insert({key,value}); // Insert only (won’t overwrite)
```

💡 Most used in interviews:

```cpp
mp[key]++;   // Frequency counting
```

---

## ✅ Access

```cpp
mp[key];     // Returns value (⚠️ creates key if not exists)
mp.at(key);  // Throws error if key not present
```

⚠️ Common Bug:

```cpp
if(mp[key])  // This creates key if not present
```

✔ Safe way:

```cpp
if(mp.count(key))
```

---

## ✅ Check Key Exists

```cpp
mp.count(key);   // Returns 1 or 0
mp.find(key);    // Returns iterator
```

Example:

```cpp
if(mp.count(5)) {
    cout << "Exists";
}
```

Difference:

| Function | Returns  |
| -------- | -------- |
| count()  | 0 or 1   |
| find()   | Iterator |

---

## ✅ Delete

```cpp
mp.erase(key);   // Remove one key
mp.clear();      // Remove all
```

---

## ✅ Size / Empty

```cpp
mp.size();
mp.empty();
```

---

## ✅ Iterate

```cpp
for(auto it : mp){
    cout << it.first << " " << it.second << endl;
}
```

OR

```cpp
for(auto &it : mp){
    cout << it.first << " " << it.second;
}
```

---

# 🔹 2️⃣ `unordered_set` (HashSet)

```cpp
#include <unordered_set>
unordered_set<int> st;
```

👉 Stores **Only Values**
👉 No duplicates
👉 Average Time: **O(1)**

---

## ✅ Insert

```cpp
st.insert(value);
```

---

## ✅ Check Exists

```cpp
st.count(value);   // 1 or 0
st.find(value);    // iterator
```

---

## ✅ Delete

```cpp
st.erase(value);
st.clear();
```

---

## ✅ Size / Empty

```cpp
st.size();
st.empty();
```

---

## ✅ Iterate

```cpp
for(auto x : st){
    cout << x << endl;
}
```

---

# 🔥 `map` vs `unordered_map` vs `unordered_set`

| Feature          | map            | unordered_map | unordered_set |
| ---------------- | -------------- | ------------- | ------------- |
| Sorted           | ✅ Yes          | ❌ No          | ❌ No          |
| Stores           | Key-Value      | Key-Value     | Only Value    |
| Duplicate Keys   | ❌              | ❌             | ❌             |
| Time Complexity  | O(log n)       | O(1) avg      | O(1) avg      |
| Implementation   | Red-Black Tree | Hash Table    | Hash Table    |
| Order Maintained | Sorted order   | Random order  | Random order  |

---

# 🎯 Most Important Interview Patterns

### 1️⃣ Frequency Counting

```cpp
for(int x : arr){
    mp[x]++;
}
```

---

### 2️⃣ Check Duplicate

```cpp
if(st.count(x)){
    cout << "Duplicate";
}
st.insert(x);
```

---

### 3️⃣ Two Sum Pattern

```cpp
for(int i=0;i<n;i++){
    int target = sum - arr[i];
    if(mp.count(target)){
        cout << "Found";
    }
    mp[arr[i]] = i;
}
```

---

# ⚠️ Important Notes

🔹 `unordered_map` is NOT sorted
🔹 Worst case time = **O(n)** (rare, hash collision)
🔹 Use `reserve(n)` for large inputs to avoid rehashing:

```cpp
mp.reserve(100000);
```

---

# 🏁 Final Quick Revision (30 Seconds)

* `unordered_map` → Key-Value
* `unordered_set` → Only Value
* `mp[key]++` → Frequency
* `mp.count(key)` → Safe existence check
* `st.count(x)` → Duplicate check
* `erase()` → Delete
* `clear()` → Remove all
* `size()` / `empty()` → Basic checks
* `map` = Sorted (O log n)
* `unordered_*` = Fast (O1 avg)

---