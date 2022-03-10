#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=5e3+5;
int D[MAXN];
int H[MAXN];


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int T;
    cin >> T;

    while(T--)
    {
        int N,A,B,X,Y;
        cin >> N >> A >> B >> X >> Y;

        for(int i=1;i<=N;i++)
        {
            cin >> H[i];
            D[i]=1<<30;
        }

        priority_queue<par,vector<par>,greater<par>>q;
        q.push(par(0,X));
        D[X] = 0;

        while(true)
        {
            int nod = q.top().second;
            int cos = q.top().first;
            q.pop();

            if(nod == Y)
            {
                cout << cos << '\n';
                break;
            }

            for(int i=1;i<=N;i++)
            {
                int nc = abs(H[i]-H[nod])<=A && abs(i-nod)<=B ? abs(H[i]-H[nod])+abs(i-nod) : H[i]+H[nod]+abs(i-nod);
                if(D[i] > cos+nc)
                {
                    D[i]=cos+nc;
                    q.push(par(D[i],i));
                }
            }
        }
    }


    return 0;
}
