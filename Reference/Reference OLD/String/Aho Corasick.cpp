#include <bits/stdc++.h>
using namespace std;

const int MAXL = 100005;
struct node{
    int dic[27], parent, link, l;
    node( int p )
    {
        parent = p;
        link = l = 0;
        for( int i = 0; i < 26; i++ )
            dic[i] = -1;
    }
};

typedef pair<int,int>par;
queue<par>Q;
vector<node>tree;
char W[MAXL], S[MAXL];

int f( char c )
{
    return c-'a';
}

void add_word( )
{
    int l = strlen(W), nod = 0;
    for( int i = 0; i < l; i++ )
    {
        if( tree[nod].dic[f(W[i])] == -1 )
            tree[nod].dic[f(W[i])] = tree.size(), tree.push_back(node(nod));
        nod = tree[nod].dic[f(W[i])];
    }
    tree[nod].l = l;
}

void links( )
{
    Q.push(par(0,0));
    int nodo, car;
    while( !Q.empty() )
    {
        nodo = Q.front().first;
        car = Q.front().second;
        Q.pop();
        for( int i = 0; i < 26; i++ )
            if( tree[nodo].dic[i] != -1 )
                Q.push(par(tree[nodo].dic[i],i));
        if( nodo == 0 || tree[0].dic[car] == nodo )continue;
        int &link = tree[nodo].link;
        link = tree[tree[nodo].parent].link;
        while( link && tree[link].dic[car] == -1 )
            link = tree[link].link;
        link = tree[link].dic[car];
        if( link == -1 )link++;
        tree[nodo].l = max(tree[nodo].l,tree[link].l);
    }
}

int autom[MAXL*5][28];
bool OK[MAXL*5][28];

int go( int nodo, int car )
{

    if( OK[nodo][car] )
        return autom[nodo][car];
    OK[nodo][car] = 1;
    if( tree[nodo].dic[car] != -1 )
        return autom[nodo][car] = tree[nodo].dic[car];
    int link = tree[nodo].link;
    while( link && tree[link].dic[car] == -1 && !OK[link][car] )
        link = tree[link].link;
    if( OK[link][car] )
        return autom[nodo][car] = autom[link][car];
    link = tree[link].dic[car];
    if( link == -1 )link++;
    return autom[nodo][car] = link;
}

int main()
{
    tree.push_back(node(0));

}
