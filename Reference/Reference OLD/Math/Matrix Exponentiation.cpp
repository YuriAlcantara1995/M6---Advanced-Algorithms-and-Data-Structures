//Matrix Exponentiation O( n^3*log(n) )
typedef vector <int> vect;
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
      for (int k = 0; k < A[i].size(); k++)
        C[i][j] += A[i][k] * B[k][j];
  return C;
}
matrix pow(const matrix &A, int e) {
  return ( e == 0 ) ? identity(A.size()) :
         ( e % 2 == 0 ) ? pow(mul(A, A), e/2) : mul(A, pow(A, e-1));
}
