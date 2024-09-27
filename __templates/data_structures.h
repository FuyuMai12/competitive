#include<bits/stdc++.h>
using namespace std;

namespace segment {
    class tree {
    public:
        int __size;
        vector<int> __main;
        vector<int> __lazy;
        tree() {}
        tree(int n) {
            __size = 1 << (__lg(n - 1) + 1);
            __main.resize(__size << 1, 0);
            __lazy.resize(__size << 1, 0);
        }
        
        void __propagate(int node) {
            if (!__lazy[node]) return;
            __main[node] += __lazy[node];
            if (node < __size) {
                __lazy[node<<1] += __lazy[node];
                __lazy[node<<1|1] += __lazy[node];
            }
            __lazy[node] = 0;
        }
        
        void __update(int node, int nl, int nr, int l, int r, int val) {
            __propagate(node);
            if (nr < l || r < nl) return;
            if (l <= nl && nr <= r) {
                __lazy[node] += val; __propagate(node);
                return;
            }
            
            __update(node<<1, nl, nl+nr>>1, l, r, val);
            __update(node<<1|1, (nl+nr>>1)+1, nr, l, r, val);
            __main[node] = max(__main[node<<1], __main[node<<1|1]);
        }
        
        int __query(int node, int nl, int nr, int i) {
            __propagate(node);
            if (nr < i || i < nl) return -1;
            if (nl == i && i == nr) return __main[node];
            
            int p1 = __query(node<<1, nl, nl+nr>>1, i);
            int p2 = __query(node<<1|1, (nl+nr>>1)+1, nr, i);
            return max(p1, p2);
        }
        
        void update(int l, int r, int val) {__update(1, 0, __size-1, l, r, val);}
        int query(int i) {return __query(1, 0, __size-1, i);}
    };
}