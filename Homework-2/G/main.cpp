#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;
int A[MAXN];
priority_queue<int,vector<int>,less<int>>q,erased;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
    {
        cin >> A[i];
        q.push(A[i]);
    }

    int Q;
    cin >> Q;

    while(Q--)
    {
        while(!erased.empty() && erased.top() == q.top())
        {
            erased.pop();q.pop();
        }
        int t;
        cin >> t;
        if(t==1)
            cout << q.top() << '\n';
        else
        {
            int pos,val;
            cin >> pos >> val;
            erased.push(A[pos]);
            q.push(val);
            A[pos]=val;
        }
    }

    return 0;
}
