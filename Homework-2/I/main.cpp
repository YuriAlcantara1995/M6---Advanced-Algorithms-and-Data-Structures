#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
int P[MAXN];
vector<int>ady[MAXN];
int C[MAXN];
int Q[MAXN];
int heap_sz;

int parent(int i) { return (i-1)/2; }

int left(int i) { return (2*i + 1); }

int right(int i) { return (2*i + 2); }


void Heapify(int pos)
{
    int l = left(pos);
    int r = right(pos);
    int smallest = pos;
    if (l < heap_sz && Q[l] < Q[smallest])
        smallest = l;
    if (r < heap_sz && Q[r] < Q[smallest])
        smallest = r;
    if (smallest != pos)
    {
        swap(Q[pos], Q[smallest]);
        Heapify(smallest);
    }

}

int pop()
{
    Q[0] = Q[heap_sz-1];
    heap_sz--;
    Heapify(0);
}

int getMin()
{
    return Q[0];
}

void insert(int val)
{
    heap_sz++;
    int pos = heap_sz - 1;
    Q[pos] = val;

    while (pos != 0 && Q[parent(pos)] > Q[pos])
    {
        swap(Q[pos], Q[parent(pos)]);
        pos = parent(pos);
    }
}


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1;i<N;i++)
    {
        cin >> P[i];
        C[P[i]]++;
    }

    for(int i=1;i<=N;i++)
        if(!C[i])
            insert(i);

    for(int i=1;i<N;i++)
    {
        int p = getMin();
        pop();
        ady[P[i]].push_back(p);
        ady[p].push_back(P[i]);
        C[P[i]]--;
        if(!C[P[i]])
            insert(P[i]);
    }

    for(int i=1;i<=N;i++)
    {
        sort(ady[i].begin(),ady[i].end());
        for(int j=0;j<ady[i].size();j++)
            cout << ady[i][j] << ' ';
        cout << '0' << '\n';
    }

    return 0;
}
