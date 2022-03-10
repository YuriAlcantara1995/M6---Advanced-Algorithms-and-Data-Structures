#define ll long long
#define llu unsigned long long
#define MAXN 55

int G[MAXN][MAXN], w[MAXN], N;
bool A[MAXN], merged[MAXN];

int StoerWagner(int n){
    int best = 1e8;
    for(int i=1;i<n;++i) merged[i] = 0;
    merged[0] = 1;

    for(int phase=1;phase<n;++phase){
        A[0] = 1;

        for(int i=1;i<n;++i){
            if(merged[i]) continue;
            A[i] = 0;
            w[i] = G[0][i];
        }

        int prev = 0,next;
        for(int i=n-1-phase;i>=0;--i){
            // hallar siguiente vertice que no esta en A
            next = -1;
            for(int j=1;j<n;++j)
                if(!A[j] && (next==-1 || w[j]>w[next]))
                    next = j;

            A[next] = true;
            if(i>0){
                prev = next;
                // actualiza los pesos
                for(int j=1;j<n;++j) if(!A[j])
                	w[j] += G[next][j];
            }
        }
        if(best>w[next]) best = w[next];

        // mezcla s y t
        for(int i=0;i<n;++i){
            G[i][prev] += G[next][i];
            G[prev][i] += G[next][i];
        }
        merged[next] = true;
    }
    return best;
}

int main(){
	char cad[2323];
	while (scanf("%s",cad) != EOF){
		N = strlen(cad);

		for(int i=0;i<N;i++) G[0][i] = cad[i]-'0';

		for(int i=1;i<N;i++){
			scanf("%s",cad);
			for(int j=0;j<N;j++) G[i][j] = cad[j]-'0';
		}
		//int src, snk;
		printf("%d\n", StoerWagner(N));


	}
}
