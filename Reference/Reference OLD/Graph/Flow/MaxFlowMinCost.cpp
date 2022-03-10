const int INF = 1e9;
typedef pair <int, int> par;

namespace MCF {
	struct edge {
		int dest, cap, flow, cost, next;

		edge() {}

		edge(int dest, int cap, int cost, int next) :
			dest(dest), cap(cap), cost(cost), next(next) {
			flow = 0;
		}
	};

	const int
		MAXV = 10e3 + 5,
		MAXE = 10e4 + 5;

	int nodes, source, sink, size;
	edge g[MAXE];
	int first[MAXV], nLast[MAXV], eLast[MAXV], cst[MAXV];

	void init(int _nodes, int _source, int _sink) {
		size = 0, nodes = _nodes, source = _source;
		sink = _sink;

		for(int i = 0; i < nodes; i++)
			first[i] = -1;
	}

	void addEdge(int u, int v, int c, int cost) {
		g[size] = edge(v, c, +cost, first[u]);
		first[u] = size++;
		g[size] = edge(u, 0, -cost, first[v]); //bidirectional, put zero if only directed edges!
		first[v] = size++;
	}

	par maxFlowMinCost() {
		int flow = 0, flowCost = 0;

		while(true) {
			priority_queue <par> q;

			for(int i = 0; i < nodes; i++)
				cst[i] = INF;

			cst[source] = 0;
			q.push(make_pair(0, source));

			while(!q.empty()) {
				int u = q.top().second;
				int c = -q.top().first;
				q.pop();

				if(u == sink)
					break;

				for(int k = first[u]; k != -1; k = g[k].next) {
					int v = g[k].dest;
					int w = g[k].cost + c;

					if(g[k].cap > g[k].flow && w < cst[v]) {
						cst[v] = w;
						nLast[v] = u;
						eLast[v] = k;
						q.push(make_pair(-w, v));
					}
				}
			}

			if(cst[sink] == INF)
				break;

			int push = INF;
			for(int u = sink; u != source; u = nLast[u])
				push = min(push, g[eLast[u]].cap - g[eLast[u]].flow);

			flow += push;
			flowCost += cst[sink] * push;

			for(int u = sink; u != source; u = nLast[u]) {
				g[eLast[u]].flow += push;
				g[eLast[u] ^ 1].flow -= push;
			}
		}

		return make_pair(flow, flowCost);
	}
}
