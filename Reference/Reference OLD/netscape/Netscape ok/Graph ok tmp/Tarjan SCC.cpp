void Tarjan_SCC( int nod ){
	Td[nod] = low[nod] = ++ k;
	P.push( nod );
	for( auto newn : V[nod] ){ 
		if( Td[newn] ){
			if( !mark[newn] )
				low[nod] = min( low[nod], Td[newn] );
			continue;
		}
		Tarjan_SCC( newn );
		low[nod] = min( low[nod], low[newn] );
	}
	if( low[nod] == Td[nod] ){
		cfc ++;
		while( !mark[nod] ){
			printf("%d ", (int)P.top());
			mark[(int)P.top()] = true;
			P.pop();
}	}	}