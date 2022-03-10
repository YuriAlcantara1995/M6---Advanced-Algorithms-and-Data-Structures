/// 1- Finding number of distinct substrings(ok)
/// 2- Total Length of all distinct substrings (mal)
/// 3- The Lexographically kth substring (ok)
/// 5- POSITION OF FIRST OCCURRENCE p -> s (ok)
/// 6- COUNT NUMBER OF OCCURRENCES( OK )
/// 7- LONGEST COMMON SUBSTRING OF TWO STRINGS

// Construct:
// Automaton sa; for(char c : s) sa.extend(c);
// 1. Number of distinct substr:
//    - Find number of different paths --> DFS on SA
//    - f[u] = 1 + sum( f[v] for v in s[u].next
// 2. Number of occurrences of a substr:
//    - Initially, in extend: s[cur].cnt = 1; s[clone].cnt = 0;
//    - for(it : reverse order)
//        p = nodes[it->second].link;
//        nodes[p].cnt += nodes[it->second].cnt
// 3. Find total length of different substrings:
//    - We have f[u] = number of strings starting from node u
//    - ans[u] = sum(ans[v] + d[v] for v in next[u])
// 4. Lexicographically k-th substring
//    - Based on number of different substring
// 5. Smallest cyclic shift
//    - Build SA of S+S, then just follow smallest link
// 6. Find first occurrence
//    - firstpos[cur] = len[cur] - 1, firstpos[clone] = firstpos[q]
// 7. Longest common substring of two strings
//	  -

#include <bits/stdc++.h>
using namespace std;

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
/// 1- Finding number of distinct substrings
vector<int>d(2*MAXLEN,0);

int distsub(int ver){  
   int tp = 1  ;

   if(d[ver])
     return d[ver];

   for(int i='a';i<='z';i++)
     if( st[ver].next[i] )
         tp+= distsub(st[ver].next[i]);

   d[ver]=tp;
   return d[ver];
}

/// 2- Total Length of all distinct substrings (mal)
vector<int>ans(MAXLEN,0);

int lesub( int ver)
{ int  tp = 0  ;//To Find Words just add length of words instead of 1

   if(ans[ver])
     return ans[ver];

   for(int i='a';i<='z';i++)
     if( st[ver].next[i] )
         tp = lesub(st[ver].next[i]) + d[st[ver].next[i]];

   ans[ver]=tp;
   return ans[ver];

}

/// 3- The Lexographically kth substring
int path, k;
vector<char>ans1;
void klex(int ver){
    for(int i='a'; i<='z'; i++)
        if( st[ver].next[i]  ){
            path++;
            if (path==k){
                ans1.push_back((char)(i));
                return;
            }
            klex(st[ver].next[i]);
            if (path==k){
                ans1.push_back((char)(i));
                return;
            }
        }
}

/// 5- POSITION OF FIRST OCCURRENCE p -> s
string p;
int firstpostn(){
   int s_t = 0 ;
   int vtx = 0;
    while(s_t<p.length())
     {
	   if( st[vtx].next.find(p[s_t]) == st[vtx].next.end() )
           return -1;
       vtx = st[vtx].next[p[s_t]];
       s_t++;
     }

   return st[vtx].fpos - p.length() + 1;
}

/// 6- COUNT NUMBER OF OCCURRENCES
int repstr(){
    set<pair<int,int>>::reverse_iterator it;

    for(  it=base.rbegin(); it!=base.rend(); it++ )
       cnt[ st[ it -> second ].link ] += cnt[ it->second ];

    int vtx = 0, s_t = 0;
    while(s_t < p.length()){
        if( st[vtx].next.find( p[s_t] ) == st[vtx].next.end() )
            return 0;
        vtx = st[vtx].next[p[s_t]];
        s_t++;
    }

   return cnt[vtx];
}
/// 7- LONGEST COMMON SUBSTRING OF TWO STRINGS
string lcs (string s, string t) {
    sa_init();
    for (int i=0; i<(int)s.length(); i++)
        sa_extend (s[i]);

    int v = 0,  l = 0, best = 0,  bestpos = 0;
    for (int i=0; i<(int)t.length(); i++) {
        while (v && ! st[v].next.count(t[i])) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next.count(t[i])) {
            v = st[v].next[t[i]];
            l++;
        }
        if (l > best)
            best = l,  bestpos = i;
    }
    return t.substr (bestpos-best+1, best);
}


int main()
{
    #ifdef acm
    freopen("a.in", "r", stdin);
    #endif // acm

    cin.tie();
    ios_base::sync_with_stdio( 0 );

    string s;
    cin >> s >> p;

    cout << lcs( s, p );

    return 0;
}
