#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
int N,K;
char S[MAXN];

bool can(int x)
{
    int lastB=1;
    int b=K-2;
    int next=lastB+x+1;
    int lastz=1;
    for(int i=2;i<N;i++)
    {
        if(S[i]=='0')
            lastz=i;

        if(i == next)
        {
            if(lastB==lastz)
                return false;

            lastB=lastz;
            b--;
            next=lastB+x+1;
        }
    }

    return b>=0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    cin >> (S+1);

    int I=0,F=N,sol=N;
    while(I<=F)
    {
        int piv=(I+F)/2;
        if(can(piv))
            sol=piv, F=piv-1;
        else
            I=piv+1;
    }

    cout << sol << '\n';


    return 0;
}
