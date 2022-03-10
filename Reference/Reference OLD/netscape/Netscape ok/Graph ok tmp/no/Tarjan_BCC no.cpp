void BCC( int nod ){
    Td[nod] = Low[nod] = ++ k;
    int newn;
	for( auto id : V[nod] ){ 
        newn = G[id].nextn( nod );
        if( !mark[id] ){
            P.push( id );
            mark[id] = true;
        }
        if( Td[newn] ){
            Low[nod] = min( Low[nod], Td[newn] );
            continue;
        }
        BCC( newn );
        Low[nod] = min( Low[newn], Low[nod] );
        if( Td[nod] <= Low[newn] ){
            num ++;
            while( !CB[id] ){
                CB[P.top()] = num;
                P.pop();
}	}	}	}