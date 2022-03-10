#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
using namespace std;

string s;
int z[100005];

int main()
{
    cin >> s;
    int n =  ( int ) s.length ( ) ;
    vector < int > pi ( n ) ;
    for  ( int I = 1 ; I < n ;  ++ I )
    {
        int j = pi [ I - 1 ] ;
        while  ( j > 0 && s [ I ]  != s [ j ] )
            j = pi [ j - 1 ] ;
        if  ( s [ I ]  == s [ j ] )   ++ j ;
        pi [ I ]  = j ;
    }
//cantidad de veces que aparece el prefijo de tamaño
//i en la cadena
    vector < int > ans ( n + 1 ) ;
    for  ( int I = 0 ; I < n ;  ++ I )
        ++ ans [ pi [ I ] ] ;
    for  ( int I = n - 1 ; I > 0 ;  -- I )
        ans [ pi [ I - 1 ] ]  += ans [ I ] ;

    for(int i=1; i<n; i++)
        printf("%d ",ans[i]+1);

//Given a string S of length n,
//the Z Algorithm produces an array Z
//where Z[i] is the length of the longest
//substring starting from S[i] which is also a prefix of S
    int L = 0, R = 0;
    for (int i = 1; i < n; i++)
    {
        if (i > R)
        {
            L = R = i;
            while (R < n && s[R-L] == s[R]) R++;
            z[i] = R-L;
            R--;
        }
        else
        {
            int k = i-L;
            if (z[k] < R-i+1) z[i] = z[k];
            else
            {
                L = i;
                while (R < n && s[R-L] == s[R]) R++;
                z[i] = R-L;
                R--;
            }
        }
    }
    cout << '\n';
    for(int i=0; i<n; i++)
        printf("%d ",z[i]);

    return 0;
}
