//Encuentra el Maximo Matching en un Grafo general donde pueden haber ciclos de tamaño impar
#include <bits/stdc++.h>
using namespace std;
#define maxN 1005
int n;
vector<int>G[maxN];
int match[maxN],Head, Tail,Queue[maxN],Start, Finish,NewBase,Father[maxN],Base[maxN];
bool InQueue[maxN], InPath[maxN], InBlossom[maxN];

void Push(int u){
	Queue[Tail++]= u;
	InQueue[u]= true;
}
int Pop(){
	return Queue[Head++];
}
int FindCommonAncestor(int u, int v){
	memset(InPath, 0, sizeof(InPath));
	while(true){
		u=Base[u];
		InPath[u]= true;
		if (u == Start)break;
		u= Father[match[u]];
	}
	while(true){
		v= Base[v];
		if (InPath[v]) break;
		v = Father[match[v]];
	}
	return v;
}
void ResetTrace(int u){
	int v;
	while (Base[u] != NewBase){
		v= match[u];
		InBlossom[Base[u]]= 1;
		InBlossom[Base[v]]= 1;
		u= Father[v];
		if (Base[u] != NewBase)Father[u]=v;
	}
}
void BlossomContract(int u,int v){
	NewBase= FindCommonAncestor(u, v);
	memset(InBlossom,0 ,sizeof(InBlossom));
	ResetTrace(u);
	ResetTrace(v);
	if (Base[u] != NewBase)Father[u]= v;
	if (Base[v] != NewBase)Father[v]= u;
	for(u=1;u<=n;u++)
		if (InBlossom[Base[u]]){
			Base[u]= NewBase;
			if (!InQueue[u]) Push(u);
		}
}
void FindAugmentingPath(){
	int u,v;
	memset(InQueue,false, sizeof(InQueue));
	memset(Father,0,sizeof(Father));
	for(u=1;u<=n;u++) Base[u]=u;
	Head= 1;
	Tail= 1;
	Push(Start);
	Finish = 0;
	while (Head < Tail){
		u= Pop();
		//for (v=1;v<=n;v++)
		for( int i = 0; i < (int)G[u].size(); i++ )
		{
		    v = G[u][i];
			if ((Base[u]!=Base[v])&&(match[u]!= v))
            {
				if ((v == Start)||((match[v] > 0)&&(Father[match[v]] > 0)))
					BlossomContract(u, v);
				else if (Father[v] == 0){
					Father[v]=u;
					if (match[v] > 0)
						Push(match[v]);
					else{
						Finish=v;
						return;
					}
				}
            }
		}
	}
}
void AugmentPath(){
	int u,v,w;
	u=Finish;
	while(u > 0){
		v=Father[u];
		w=match[v];
		match[v]= u;
		match[u]= v;
		u= w;
	}
}
void PrintMatch(){
	int u,sol;
	sol = 0;
	for(u=1;u<=n;u++)
		if (u < match[u])sol++;
	printf("%d\n",sol*2);
}


void Edmonds(){
	int u;
	//memset(match,0,sizeof(match));
	for(u=1;u<=n;u++)
		if (match[u]==0){
			Start=u;
			FindAugmentingPath();
			if (Finish > 0) AugmentPath();
		}
}

void BuildPreMatch()
{
	memset(match,0,sizeof(match));
    for( int i = 1; i <= n; i++ )
    {
        if( match[i] )
            continue;
        for( int j = 0; j < (int)G[i].size(); j++ )
        {
            if( match[G[i][j]] )
                continue;
            match[i] = G[i][j];
            match[G[i][j]] = i;
            break;
        }
    }
}
int main(){

        freopen("edmonds.in","r",stdin);
        freopen("edmonds.out","w",stdout);

        scanf("%d",&n);

        int a, b;
        while( cin >> a >> b )
        {
            G[a].push_back(b);
            G[b].push_back(a);
        }

        BuildPreMatch();
		Edmonds();
		PrintMatch();

	return 0;
}
