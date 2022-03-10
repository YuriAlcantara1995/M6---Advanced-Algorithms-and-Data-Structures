#include <bits/stdc++.h>
using namespace std;
const int maxn=40011,maxq=100011;
int BLOCK;
struct node{
	int l, r, i, sp, ans;
}Q[maxq];
int lvl[maxn], p[maxn][16], st[maxn], en[maxn], id[2*maxn], occ[maxn], ans, w[maxn];
map<int, int> HASH;
int cnt[maxn];
vector<int> g[maxn];
int ti;
bool f(node a, node b){
	if (a.l/BLOCK != b.l/BLOCK)
		return a.l < b.l;
	return a.r < b.r;
}
bool gg(node a, node b){
	return a.i < b.i;
}
void dfs(int u, int p){

	st[u] = ++ti;
	id[ti] = u;
	int v;
	for(auto v: g[u]){
		if (v == p)
			continue;
		lvl[v] = lvl[u]+1;
		::p[v][0] = u;
		dfs(v, u);
	}
	en[u] = ++ti;
	id[ti] = u;
}
int lca(int u, int v){
	int lg, i;
	for (lg = 0; (1<<lg) <= lvl[u]; lg++);
	lg--;
	for(i=lg; i>=0; i--)
		if ( lvl[u] - (1<<i) >= lvl[v])
			u = p[u][i];
	if (u == v)
		return u;
	for(i = lg; i >= 0; i--){
		if (p[u][i] != -1 && p[u][i] != p[v][i])
			u = p[u][i], v = p[v][i];
	}
	return p[u][0];
}
void add(int node){
	occ[node]++;
	cnt[w[node]]++;
	if (occ[node] == 2){
		cnt[w[node]] -= 2;
		if (cnt[w[node]] == 0)
			ans--;
	}
	else if (cnt[w[node]] == 1) ans++;
}
void del(int node){
	int wt = w[node];
	occ[node]--;

	if (occ[node] == 1){
		cnt[wt]++;
		if (cnt[wt] == 1)
			ans++;
		return;
	}
	cnt[wt]--;
	if (cnt[wt] == 0) ans--;
}
int main() {
	ios_base::sync_with_stdio(false);
	int n, m, i, j, u, v;
	ans = ti = 0;
	cin>>n>>m;
	BLOCK = sqrt(n);
	int no = 0;
	HASH.clear();
	//compress coordinates
	for( int i = 1; i <= n; i++ ){
		cin>>w[i];
		if (HASH.find(w[i]) == HASH.end())
			HASH[w[i]] = ++no;
		w[i] = HASH[w[i]];

	}
	//read de graph
	for( int i = 1; i < n; i++ ){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	lvl[1] = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(occ, 0, sizeof(occ));
	memset(p, -1, sizeof(p));
	//compute the necesary values
	dfs(1, 0);
	//compute lca
	for(i=1; i<16; i++)
	for(j=1; j<=n; j++)
		if( p[j][i-1] != -1)
			p[j][i] = p[p[j][i-1]][i-1];

    //read th queries
	for( int i = 1; i <= m; i++){
		Q[i].i = i;
		Q[i].sp = -1;
		cin>>u>>v;
		if (lvl[u] < lvl[v])
			swap(u, v);
		int w = lca(u, v);
		//case 1
		if (w == v){
			Q[i].l = st[v];
			Q[i].r = st[u]+1;
		}//case 2
		else{
			if (st[v] > en[u]){
				Q[i].l = en[u];
				Q[i].r = st[v]+1;
			}
			else{
				Q[i].l = en[v];
				Q[i].r = st[u]+1;
			}
			// Special case: We have to consider 'w' separately.
			Q[i].sp = w;
		}
	}
	sort(Q, Q+m, f);
	int currL = 0, currR = 0, L, R;
	for( int i = 1; i <= m; i++ ){
		L = Q[i].l, R = Q[i].r;
		while (currL < L){
			del(id[currL]);
			currL++;
		}
		while (currL > L){
			add(id[currL-1]);
			currL--;
		}
		while (currR < R){
			add(id[currR]);
			currR++;
		}
		while (currR > R){
			del(id[currR-1]);
			currR--;
		}
		Q[i].ans = ans;
		if (Q[i].sp != -1){
			if (cnt[w[Q[i].sp]] == 0)
				Q[i].ans = ans+1;
		}
	}
	sort(Q, Q+m, gg);
	for( int i = 1; i <= m; i++ )
		cout<<Q[i].ans<<endl;

	return 0;
}
