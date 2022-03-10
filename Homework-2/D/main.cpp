#include <bits/stdc++.h>
using namespace std;

priority_queue<int,vector<int>,greater<int>>q;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
    {
        int K;
        cin >> K;
        int x;
        while(K--)
        {
            cin >> x;
            q.push(x);
        }
    }

    while(!q.empty())
    {
        if(q.size()==1)
            cout << q.top() << '\n';
        else
            cout << q.top() << ' ';

        q.pop();
    }

    return 0;
}
