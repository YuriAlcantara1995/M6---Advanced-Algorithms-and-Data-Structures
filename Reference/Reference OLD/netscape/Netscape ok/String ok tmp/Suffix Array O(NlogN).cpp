int n, _sa[LEN], _b[LEN],  top[LEN], _tmp[LEN];
int LCP[LEN], *SA = _sa, *B = _b, *tmp = _tmp;
char s[LEN];
void build_lcp (){
    for(int i = 0, k = 0; i < n; ++i){
        if(B[i] == n - 1)
            continue;
        for(int j = SA[B[i] + 1]; i + k < n && 
				j + k < n && s[i+k] == s[j + k]; k++);
        LCP[B[i]] = k;
        if( k ) k--;
    }
}
void build_sa (){
	//memset 0 -> _sa, _b, _tmp, top, LCP
    s[n] = '\0', n ++;
    int na = (n < 256 ? 256 : n);
    for (int i = 0; i < n ; i++)
        top[B[i] = s[i]]++;
    for (int i = 1; i < na; i++)
        top[i] += top[i - 1];
    for (int i = 0; i < n ; i++)
        SA[--top[B[i]]] = i;
    for (int ok = 1,j = 0;ok < n && j < n-1;ok <<= 1){
        for (int i = 0; i < n; i++){
            j = SA[i] - ok;
            if (j < 0)
                j += n;
            tmp[top[B[j]]++] = j;
        }
        SA[tmp[top[0] = 0]] = j = 0;
        for (int i = 1; i < n; i++){
            if (B[tmp[i]] != B[tmp[i - 1]] || 
				B[tmp[i]+ok] != B[tmp[i-1] + ok])
                top[++j] = i;
            SA[tmp[i]] = j;
        }
        swap(B, SA), swap(SA, tmp);
    }
    build_lcp();
    n --, s[n] = '\0';
}