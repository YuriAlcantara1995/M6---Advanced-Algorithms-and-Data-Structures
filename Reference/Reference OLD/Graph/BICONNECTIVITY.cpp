#include <stack>
#include <vector>
#include <iostream>
#define OVERALL_TIME "O(V+E)"

using namespace std;

const int
      MaxV = 1001,
	  MaxE = 10001;

typedef pair<int, int> pii;

int V, E;
int i, j;
int a, b;
int size;
int gtime;
stack <pii> Q;
int disc[MaxV];
int back[MaxV];
bool mark[MaxE];
vector<pii> bic[MaxV];
vector<pii> graph[MaxV];

void dfs(int v) {
    gtime++;
    disc[v] = gtime;
	back[v] = gtime;
	for (int k = graph[v].size() - 1; k >= 0; k--) {
	    int next = graph[v][k].first;
		int edge = graph[v][k].second;
		if (!mark[edge]) {
		    Q.push(pii(v, next));
			mark[edge] = true;
		}
		if (!disc[next]) {
			dfs(next);
			back[v] = min(back[v], back[next]);
			if (back[next] >= disc[v]) {
			    size++;
			    for (;;) {
				    pii x = Q.top(); Q.pop();
					bic[size].push_back(x);
					if (x == pii(v, next))
					    break;
				}
			}
		} else back[v] = min(back[v], disc[next]);
	}
}

int main() {

	cin >> V >> E;
	for (i = 0; i < E; i++) {
	    cin >> a >> b;
		graph[a].push_back(pii(b, i));
		graph[b].push_back(pii(a, i));
	}
	
	for (i = 1; i <= V; i++)
	    if (!disc[i]) dfs(i);
	
	for (i = 1; i <= size; i++) {
	    cout << "Biconnected Component: " << i << endl;
		for (j = bic[i].size() - 1; j >= 0; j--)
		    cout << bic[i][j].first << " " << bic[i][j].second << endl;
	}
	
    return 0;
}
