//el steiner tree es un caso especiel de mst donde en este no se abarca necesariamente todo el conjunto de nodos
//sino un subconjunto estpecifico de estos permitiendo el uso de algunos nodos intermedios
//Complejidad (2^cTerminales)*N^2 cTerminales->numero de nodos terminales N->numero de nodos totales
//incluidos los terminales.

for( int i = 1; i < (1 << CTerminal); i++ )
	for( int j = 0; j < N; j++ )
		dp[i][j] = oo;

//importante caso base cuando el nodo terminal es la raiz de su arbol
//mask = 1 << i i->id del nodo con respecto a los terminales,
//id_terminal = id del nodo con respecto a todos los nodos
for( int i = 0; i < cTerminal; i++ )
	dp[1 << i][id_terminal] = 0;

//dp para computar el minimo steiner tree
//los estados son teniendo a root como raiz del arbol y a mask como los nodos terminales que
//estan en el arbol
for( int mask = 1; mask < (1 << cTerminal); mask++ ){
	for( int root = 0; root < N; root ++ ){
		for( int smask = mask; smask; smask = (smask-1)&mask ){
			dp[mask][root] = min(dp[mask][root], dp[smask][root]+dp[mask^smask][root]);
		}
		//ciclo para mover la raiz del arbol
		if( dp[mask][root] < oo ){
			for( int j = 0; j < N; j++ )
				dp[mask][j] = min(dp[mask][j],dp[mask][root] + C[root][j]);
		}
	}
}

//sol = min(dp[1 << Cterminal][i])