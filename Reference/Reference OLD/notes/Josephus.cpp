#include<bits/stdc++.h>
using namespace std;

int josephus(int n,int k)
{
    int i,result;
    for(i=1,result=0;i<=n;i++)
        result=(result+k-1)%i+1;
 return result-1;
}

int main(){

	int n, k;
	cin >> n >> k;
	cout << josephus(n,k);//+1 si los indices comienzan desde 1
}
