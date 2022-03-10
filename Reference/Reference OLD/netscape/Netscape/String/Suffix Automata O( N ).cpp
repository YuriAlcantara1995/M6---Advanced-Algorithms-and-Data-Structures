// Construct:
// Automaton sa; for(char c : s) sa.extend(c);
// 1. Number of distinct substr O( N ):
//    - Find number of different paths --> DFS on SA
//    - f[u] = 1 + sum( f[v] for v in s[u].next
// 2. Number of occurrences of a substr O( N ):
//    - Initially, in extend: s[cur].cnt = 1; s[clone].cnt = 0;
//    - for( auto it = base.rbegin(); it != base.rend(); it ++ ){
//        int p = st[it->second].link;
//        cnt[p] += cnt[it->second];  }
// 3. Find total length of different substrings O( N ):
//    - We have f[u] = number of strings starting from node u
//    - ans[u] = sum(ans[v] + d[v] for v in next[u])
// 4. Lexicographically k-th substring O(N)
//    - Based on number of different substring
// 5. Find first occurrence O(N)
//    - firstpos[cur] = len[cur] - 1, firstpos[clone] = firstpos[q]
// 6. Longest common substring of two strings s, t O(N).
struct state {
    int len, link;
    int fpos;///
    map<char,int>next;
    state( ){
        len = 0, link = -1, fpos = 0;
        next.clear();
    }
};
const int MAXLEN = 100002;
state st[MAXLEN*2];
int sz, last;
set<pair<int,int>> base ;///
int cnt[MAXLEN*2];///
void sa_init() {
    sz = last = 0;
    st[0] = state();
	cnt[0] = 0;
    sz++;
    base.clear();
}
void sa_extend (char c) {
    int cur = sz++;
    st[cur] = state();
    st[cur].len = st[last].len + 1;
    st[cur].fpos = st[cur].len - 1;///
    cnt[cur] = 1 ; /// 
    base.insert(make_pair(st[cur].len, cur));///
    int p;
    for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
        st[p].next[c] = cur;
    if (p == -1)
        st[cur].link = 0;
    else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len)
            st[cur].link = q;
        else {
            int clone = sz++;
            st[clone] = state();
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].fpos = st[q].fpos;///
            cnt[clone]=0;///
            base.insert(make_pair(st[clone].len,clone)); ///
            for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                st[p].next[c] = clone;
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
//6. Longest common substring of two strings s, t.
string lcs (string s, string t) {
    sa_init();
    for (int i=0; i<(int)s.length(); i++)
        sa_extend (s[i]);
    int v = 0,  l = 0, best = 0,  bestpos = 0;
    for (int i=0; i<(int)t.length(); i++) {
        while (v && !st[v].next.count(t[i])) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next.count(t[i])) {
            v = st[v].next[t[i]];
            l++;
        }
        if (l > best) best = l,  bestpos = i;
    }
    return t.substr (bestpos-best+1, best);
}