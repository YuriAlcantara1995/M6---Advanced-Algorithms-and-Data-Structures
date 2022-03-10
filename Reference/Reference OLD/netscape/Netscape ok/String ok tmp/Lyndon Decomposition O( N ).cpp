/*s = w1w2w3..wk, w1 >= w2 >=...>= wk.
  > Menor Rotación Lexicográfica:Es el mayor valor 
  de i, tal que i < n, en la descomposicion de lyndon
  de la cadena s+s, n = |s|  */
void lyndon( string s ){
    int n = (int)s.length(), i = 0;
    while( i < n ){
        int j = i+1, k = i;
        while( j < n && s[k] <= s[j] ){
            if( s[k] < s[j] ) k = i;
            else k ++;
            j ++;
        }
        while( i <= k ){
            cout << s.substr( i, j-k )<<endl;
            i += j-k;
}    }    }