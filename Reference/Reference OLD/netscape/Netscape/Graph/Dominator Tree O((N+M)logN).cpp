struct graph{
	int n;
	vector<vector<int> > adj, radj, to;
	graph(int n) : n(n), adj(n), radj(n), to(n) {}
	void add_edge(int src, int dst){
		adj[src].push_back(dst);
		radj[dst].push_back(src);
	}
	vector<int> rank, semi, low, anc;
	int eval(int v){
		if (anc[v] < n && anc[anc[v]] < n){
			int x = eval(anc[v]);
			if (rank[semi[low[v]]] > rank[semi[x]])
				low[v] = x;
			anc[v] = anc[anc[v]];
		}
		return low[v];
	}
	vector<int> prev, ord;
	void dfs(int u){
		rank[u] = ord.size();
		ord.push_back(u);
		for (int i = 0; i < (int) adj[u].size(); ++i){
			int v = adj[u][i];
			if (rank[v] < n)
				continue;
			dfs(v);
			prev[v] = u;
		}
	}
	vector<int> idom; // idom[u] is an immediate dominator of u
	void dominator_tree(int r){
		idom.assign(n, n);
		prev = rank = anc = idom;
		semi.resize(n);
		for (int i = 0; i < n; ++i)
			semi[i] = i;
		low = semi;
		ord.clear();
		dfs(r);
		vector<vector<int> > dom(n);
		for (int x = (int) ord.size() - 1; x >= 1; --x){
			int w = ord[x];
			for (int j = 0; j < (int) radj[w].size(); ++j){
				int v = radj[w][j];
				int u = eval(v);
				if (rank[semi[w]] > rank[semi[u]])
					semi[w] = semi[u];
			}
			dom[semi[w]].push_back(w);
			anc[w] = prev[w];
			for (int i=0;i<(int)dom[prev[w]].size();++i){
				int v = dom[prev[w]][i];
				int u = eval(v);
				idom[v] = (rank[prev[w]] > rank[semi[u]]? 
								u : prev[w]);
			}
			dom[prev[w]].clear();
		}
		for (int i = 1; i < (int) ord.size(); ++i){
			int w = ord[i];
			if (idom[w] != semi[w])
				idom[w] = idom[idom[w]];
		}
	}
	vector<int> dominators(int u){
		vector<int> S;
		for (; u < n; u = idom[u])
			S.push_back(u);
		return S;
	}
	void tree(  ){
		for (int i = 0; i < n; ++i){
			if (idom[i] < n)
				to[ idom[i] ].push_back( i );
		}
	}
};