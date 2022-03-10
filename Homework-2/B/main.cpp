#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
typedef long long ll;
typedef pair<int,int>par;
vector<par>swaps;
int A[MAXN];
int N;


int left(int pos)
{
    return 2*pos+1;
}

int right(int pos)
{
    return 2*pos+2;
}

void Heapify(int pos)
{
    int l = left(pos);
    int r = right(pos);
    int biggest = pos;
    if (l < N && A[l] > A[biggest])
        biggest = l;
    if (r < N && A[r] > A[biggest])
        biggest = r;
    if (biggest != pos)
    {
        swap(A[pos], A[biggest]);
        swaps.push_back(par(pos,biggest));
        Heapify(biggest);
    }
}

int getMin()
{
    int ret = A[0];
    swap(A[0],A[N-1]);
    N--;
    Heapify(0);

    return ret;
}


int main() {

    cin >> N;
    for(int i=0;i<N;i++)
        cin >> A[i];

    for(int i=N-1;i>=0;i--)
        Heapify(i);


    int sz=N;
    vector<int>v;
    for(int i=1;i<=sz;i++)
        v.push_back(getMin());

    cout << swaps.size() << '\n';
    reverse(v.begin(),v.end());
    for(int i=0;i<v.size()-1;i++)
        cout << v[i] << ' ';
    cout << v[v.size()-1] << '\n';

    return 0;
}
