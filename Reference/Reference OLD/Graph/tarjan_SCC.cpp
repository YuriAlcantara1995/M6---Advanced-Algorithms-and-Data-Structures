TARJAN_SCC
 
using namespace std;
 
int N, M, low[10005], Td[10005], k, sol;
stack<int> P;
vector<int> V[10005];
bool mark[10005];
 
void Tarjan_SCC( int nod )
{
 int newn;
 vector<int>::iterator it;
 Td[nod] = low[nod] = ++ k;
 P.push( nod );
 
 for(it = V[nod].begin(); it != V[nod].end(); it ++)
 {
  newn = *it;
 
  if( Td[newn] )
  {
   if( !mark[newn] )
    low[nod] = min( low[nod], Td[newn] );
 
   continue;
  }
 
  Tarjan_SCC( newn );
  low[nod] = min( low[nod], low[newn] );
 }
 
 if( low[nod] == Td[nod] )
 {
  sol ++;
  printf("SCC %d: ", sol);
  while( !mark[nod] )
  {
   printf("%d ", (int)P.top());
   mark[(int)P.top()] = true;
   P.pop();
  }
 
  printf("\n");
 }
}
 
int main()
{
 scanf("%d%d", &N, &M);
 
 int a, b;
 for(int i = 1; i <= M; i ++)
 {
  scanf("%d%d", &a, &b);
  V[a].push_back( b );
 }
 
 for(int i = 1; i <= N; i ++)
  if( !Td[i] )
   Tarjan_SCC ( i );
 
        return 0;
}
