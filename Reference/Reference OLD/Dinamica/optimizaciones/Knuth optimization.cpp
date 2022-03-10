It is applicable in the case where recurrence is in the form :
dp[i][j]=min i <k<j {dp[i][k]+dp[k][j]}+C[i][j]

The sufficient condition for applicability is:
A[i,j-1] = A[i, j] = A[i + 1, j]

Where,
    A[i][j] � the smallest k that gives optimal answer, for example in:
    dp[i][j] = dp[i - 1][k] + C[k][j]
    C[i][j] � given cost function

	

    for (int s = 0; s<=k; s++)                      //s - length(size) of substring
        for (int l = 0; l+s<=k; l++) {              //l - left point
          int r = l + s;                            //r - right point
          if (s < 2) {                              
            res[l][r] = 0;                          //DP base - nothing to break
            mid[l][r] = l;                          //mid is equal to left border
            continue;
          }
          int mleft = mid[l][r-1];                  //Knuth's trick: getting bounds on m
          int mright = mid[l+1][r];
          res[l][r] = 1000000000000000000LL;
          for (int m = mleft; m<=mright; m++) {     //iterating for m in the bounds only
            int64 tres = res[l][m] + res[m][r] + (x[r]-x[l]);
            if (res[l][r] > tres) {                 //relax current solution
              res[l][r] = tres;
              mid[l][r] = m;
            }
          }
        }
      int64 answer = res[0][k];