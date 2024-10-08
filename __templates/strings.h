#include<bits/stdc++.h>
using namespace std;

namespace strings {
    vector<int> z_algo(string &str) {
        int n = str.size();
        vector<int> z(n);
        int x = 0, y = 0;
        for (int i=1; i<n; i++) {
            z[i] = max(0, min(z[i-x], y - i + 1));
            while (i + z[i] < n && str[z[i]] == str[i + z[i]]) {
                x = i; y = i + z[i]; z[i]++;
            }
        }
        return z;
    }

    int ManacherProcess(string &s) {
        int n = s.size(), res = 0;
        vector<int> odd(n, 0), even(n, 0);
        for (int i=0, l=0, r=-1; i<n; i++) {
            int x = 0; if (i <= r) x = min(odd[l+r-i], r-i);
            while (0 <= i-x-1 && i+x+1 < n && s[i-x-1] == s[i+x+1]) x++;
            odd[i] = x; res += (x + 1);
            if (i + x > r) {l = i - x; r = i + x;}
        }
        for (int i=1, l=0, r=0; i<n; i++) {
            if (s[i-1] != s[i]) continue;
            int x = 0; if (i <= r) x = min(even[l+r-i+1], r-i);
            while (0 <= i-x-2 && i+x+1 < n && s[i-x-2] == s[i+x+1]) x++;
            even[i] = x; res += (x + 1);
            if (i + x > r) {l = i-1 - x; r = i + x;}
        }
        return res;
    }
}