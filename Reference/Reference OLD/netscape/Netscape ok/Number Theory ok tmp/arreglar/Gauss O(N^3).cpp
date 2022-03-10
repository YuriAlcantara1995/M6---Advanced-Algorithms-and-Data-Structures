typedef vector<double> arr;
typedef vector<arr> matrix;
arr gauss( matrix mat, arr s, int n ){
    arr X(n);
    for( int k = 0; k < n; k ++ ){
        for( int i = k+1; i < n; i ++ ){
            s[i] = s[i] - mat[i][k]*s[k]/mat[k][k];
            for( int j = n-1; j >= k; j -- )
                mat[i][j] = mat[i][j] - 
							mat[k][j]*mat[i][k]/mat[k][k];
        }
    }
    for( int k = n-1; k >= 0; k -- ){
        double v = 0;
        for( int i = k+1; i < n; i ++ )
            v += mat[k][i]*X[i];
        X[k] = (s[k] - v)/mat[k][k];
    }
    return X;
}