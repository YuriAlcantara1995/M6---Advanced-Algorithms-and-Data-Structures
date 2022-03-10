#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
vector<int>ady[MAXN];
int diameter;

int max_distance(int nod)
{
    int md = 0;
    for(auto nn:ady[nod])
    {
        int d = max_distance(nn);
        diameter = max(diameter,md+ d + 1);
        md = max(md, 1 + d);
    }

    return md;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    int p;
    for(int i=2;i<=N;i++)
    {
        cin >> p;
        ady[p].push_back(i);
    }

    max_distance(1);

    cout << diameter << '\n';

    return 0;
}
