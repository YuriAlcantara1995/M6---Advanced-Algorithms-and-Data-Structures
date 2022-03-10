void build( ){ // O(n*m*log(n)*log(m))
	for(int i = 0; i < n ; i ++){
	  for(int j = 0; j < m ; j ++)
		table[0][0][i][j] = Matrix[i][j];
	  for(int lj = 1; lj <= log2( m ); lj ++)
		for(int j = 0; j + (1<<(lj-1)) < m; j ++)
            table[0][lj][i][j] =
		       min(table[0][lj-1][i][j],
			     table[0][lj-1][i][j+(1<<(lj-1))]);
	}
	for(int li = 1; li <= log2(n); li ++ )
	  for(int i = 0; i < n; i ++ )
		for(int lj = 0; lj <= log2(m); lj++ )
		  for(int j = 0; j < m; j ++ )
			table[li][lj][i][j] =
			    min(table[li-1][lj][i][j],
				   table[li-1][lj][i+(1<<(li-1))][j]);
}
int Query(int x1,int y1,int x2,int y2){
	int lenx=x2-x1+1;
    int kx=log2(lenx);
    int leny=y2-y1+1;
    int ky=log2(leny);
	int min_R1 = min ( table[kx][ky][x1][y1] ,
	               table[kx][ky][x1][y2-(1<<ky) + 1] );
	int min_R2 = min ( table[kx][ky][x2-(1<<kx) + 1][y1],
	               table[kx][ky][x2-(1<<kx)+1][y2-(1<<ky)+1] );
	return min ( min_R1, min_R2 );
}