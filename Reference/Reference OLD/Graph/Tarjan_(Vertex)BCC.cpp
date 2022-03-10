//Tarjan BCC
void BCC( int nod ){
    Td[nod] = Low[nod] = ++ k;
    int newn, id;
    vector<int>::iterator it;
    for( it = V[nod].begin(); it != V[nod].end(); it ++ ){
        id = *it;
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
            }
        }
    }
}
