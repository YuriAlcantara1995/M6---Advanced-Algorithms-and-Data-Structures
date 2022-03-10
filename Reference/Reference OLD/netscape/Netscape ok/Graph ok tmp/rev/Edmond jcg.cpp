struct MaxMatching {
	static const int MaxV = 1001;
	int V, E;
	int match[MaxV];
	int head, tail, Q[MaxV];
	int start, finish;
	int newbase;
	int father[MaxV], base[MaxV];
	bool graph[MaxV][MaxV];
	int queue[MaxV];
	bool inpath[MaxV];
	bool inblossom[MaxV];
	bool inqueue[MaxV];

	void initialize(int __nodes){
		V = __nodes;
		memset(graph,false,sizeof(graph));
	}
	void addEdge(int u, int v){
		graph[u][v] = true;
		graph[v][u] = true;
	}
	void push(int u){
		Q[tail++] = u;
		inqueue[u] = true;
	}
	int pop(){ return Q[head++]; }
	int findCommonAncestor(int u, int v){
		memset(inpath,0,sizeof(inpath));
		while(true){
			u = base[u];
			inpath[u] = true;
			if(u == start) break;
			u = father[match[u]];
		}
		while(true){
			v = base[v];
			if(inpath[v]) break;
			v = father[match[v]];
		}
		return v;
	}
	void resetTrace(int u){
		while(base[u] != newbase){
			int v = match[u];
			inblossom[base[u]]= true;
			inblossom[base[v]]= true;
			u = father[v];
			if(base[u] != newbase) father[u] = v;
		}
	}
	void  blossomContract(int u, int v){
		newbase = findCommonAncestor(u,v);
		memset(inblossom,false,sizeof(inblossom));
		resetTrace(u);
		resetTrace(v);
		if(base[u] != newbase) father[u]= v;
		if(base[v] != newbase) father[v]= u;
		for(int i = 1; i <= V; ++i)
			if(inblossom[base[i]]){
				base[i] = newbase;
				if(!inqueue[i]) push(i);
			}
	}
	void find_augmenting_path()	{
		memset(inqueue,false,sizeof(inqueue));
		memset(father,0,sizeof(father));
		for(int i = 1; i <= V; ++i) base[i] = i;
		head = 0;
		tail = 0;
		push(start);
		finish = 0;
		while(head < tail){
			int u = pop();
			for(int v = 1; v <= V; ++v)
				if(graph[u][v] && (base[u] != base[v]) && (match[u] != v)){
					if((v == start) || ((match[v] > 0) && (father[match[v]] > 0))){
						blossomContract(u,v);
						continue;
					}
					if(father[v] == 0){
						father[v] = u;
						if(match[v] > 0) push(match[v]);
						else{
							finish = v;
							return;
						}
					}
				}
		}
	}
	void augment_path(){
		int u = finish;
		while(u > 0){
			int v = father[u];
			int w = match[v];
			match[v] = u;
			match[u] = v;
			u = w;
		}
	}
	int edmonds(){
		memset(match,0,sizeof(match));
		for(int i = 1; i <= V; ++i)
			if(!match[i]){
				start = i;
				find_augmenting_path();
				if(finish > 0) augment_path();
			}
		int ans = 0;
		for(int i = 1; i <= V; ++i)
			if(match[i]) ++ans;
		return ans / 2;
	}
} edmond;
