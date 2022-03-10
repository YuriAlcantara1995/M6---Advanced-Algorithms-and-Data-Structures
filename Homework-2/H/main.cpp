#include <bits/stdc++.h>
using namespace std;

typedef vector<int>vi;
const int MAXN=3e5+5;
vi E[MAXN];
vi S[MAXN];

priority_queue<int,vector<int>,less<int>>q,erased;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int L,N;
    cin >> L >> N;

    int e=0;
    for(int i=1;i<=N;i++)
    {
        int l,r,c;
        cin >> l >> r >> c;
        S[i]=vi{l,r,c};
        E[++e] = vi{l+1,1,i};
        E[++e] = vi{r+1,-1,i};
    }

    sort(E+1,E+e+1);

    int j=1;
    for(int i=1;i<=L;i++)
    {
        while(j<=e && E[j][0]<=i)
        {
            int lor = E[j][1];
            int id = E[j][2];

            if(lor==-1)
                erased.push(id);
            else
                q.push(id);

            j++;
        }

        while(!erased.empty() && erased.top() == q.top())
        {
            erased.pop();
            q.pop();
        }

        if(i==L)
        {
            if(q.empty())
                cout << '0' << '\n';
            else
                cout << S[q.top()][2] << '\n';
        }
        else
        {
            if(q.empty())
                cout << '0' << ' ';
            else
                cout << S[q.top()][2] << ' ';
        }

    }



    return 0;
}
