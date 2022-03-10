typedef vector <ll> vect;
typedef vector < vect > matrix;
matrix identity (int n) {
   matrix A(n, vect(n));
   for (int i = 0; i <n; i++) A[i][i] = 1;
   return A;
 }
matrix mul(const matrix &A, const matrix &B) {
  matrix C(A.size(), vect(B[0].size()));
  for (int i = 0; i < C.size(); i++)
    for (int j = 0; j < C[i].size(); j++)
      for (int k = 0; k < A[i].size(); k++){
        C[i][j] += (A[i][k] * B[k][j])%mod;
		C[i][j] %= mod;
	  }
  return C;
}
matrix powm(const matrix &A, ll e) {
  return ( e == 0 ) ? identity(A.size()) :
         ( e % 2 == 0 ) ? powm(mul(A, A), e/2) : 
						  mul(A, powm(A, e-1));
}