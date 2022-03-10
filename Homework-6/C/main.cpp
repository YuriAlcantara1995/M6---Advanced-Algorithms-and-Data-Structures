#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int a1,b1,a2,b2;
    cin >> a1 >> b1 >> a2 >> b2;

    int h1,m1;
    cin >> h1 >> m1;

    int h2,m2;
    cin >> h2 >> m2;

    queue<par>q;
    map<par,int>C;
    q.push(par(h1,m1));
    C[par(h1,m1)] = 0;
    while(!q.empty())
    {
        par x = q.front();
        q.pop();

        par nh1 = par((x.first+a1)%24,(x.second+b1)%60);
        par nh2 = par((x.first+a2)%24,(x.second+b2)%60);

        if(C.find(nh1) == C.end())
        {
            C[nh1]=C[x]+1;
            q.push(nh1);
        }

        if(C.find(nh2) == C.end())
        {
            C[nh2]=C[x]+1;
            q.push(nh2);
        }
    }

    if(C.find(par(h2,m2)) != C.end())
        cout << C[par(h2,m2)] << '\n';
    else
        cout << "-1\n";

    return 0;
}
