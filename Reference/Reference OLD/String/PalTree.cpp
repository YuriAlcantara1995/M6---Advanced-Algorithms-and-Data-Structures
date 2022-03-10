#include "bits/stdc++.h"
using namespace std;

#define maxn  1000

struct Node
{
    int start, end, length, insertEdg[26], suffixEdg;
};

Node tree[maxn], root1, root2;
int currNode, ptr;
string s;

void insert(int idx)
{
    int tmp = currNode;
    while (true){
        int curLength = tree[tmp].length;
        if (idx - curLength >= 1 and s[idx] == s[idx-curLength-1])
            break;
        tmp = tree[tmp].suffixEdg;
    }
    if(tree[tmp].insertEdg[s[idx]-'a'] != 0){
        currNode = tree[tmp].insertEdg[s[idx]-'a'];
        return;
    }
    ptr++;
    tree[tmp].insertEdg[s[idx]-'a'] = ptr;
    tree[ptr].length = tree[tmp].length + 2;
    tree[ptr].end = idx;
    tree[ptr].start = idx - tree[ptr].length + 1;
    tmp = tree[tmp].suffixEdg;
    currNode = ptr;
    if (tree[currNode].length == 1)
    {
        tree[currNode].suffixEdg = 2;
        return;
    }
    while (true)
    {
        int curLength = tree[tmp].length;
        if (idx-curLength >= 1 and s[idx] == s[idx-curLength-1])
            break;
        tmp = tree[tmp].suffixEdg;
    }
	tree[currNode].suffixEdg = tree[tmp].insertEdg[s[idx]-'a'];
	//do things with the tree...
}

void init_tree(){
	root1.length = -1;
    root1.suffixEdg = 1;
    root2.length = 0;
    root2.suffixEdg = 1;
    tree[1] = root1;
    tree[2] = root2;
    ptr = 2;
    currNode = 1;
}
int main()
{
	init_tree();
	s = "abcbab";
    int l = s.length();

    for (int i=0; i<l; i++)
        insert(i);

    cout << "All distinct palindromic substring for "
         << s << " : \n";
    for (int i=3; i<=ptr; i++)
    {
        cout << i-2 << ") ";
        for (int j=tree[i].start; j<=tree[i].end; j++)
            cout << s[j];
        cout << endl;
    }

    return 0;
}
