#include<bits/stdc++.h>
using namespace std;

long long primesSquared[1000005];
bool B[1000005];
int r;

//recurse(1,1,m) calcula la cantidad de enteros menores o
//iguales que m que tienen un primo cuadrado como factor
//(principio de inclusion-exclusion)
// no hay que preocuparse por muchos calculos porque el
// producto de los 6 primeros primos cuadrados  4*9*25*49*121*169 = 901,800,900

//idx is the index of the prime we are looking at
//soFar is the product of some primes squared
//k is as described above
//this returns the number of integers
//less than or equal to k which have
//soFar and some prime squared as a factor
   long long recurse(int idx, long long soFar,long long k){
      long long ret = 0;
//If primesSquared[idx]*soFar > k,
//then floor(primesSquared[idx]*soFar/k) == 0,
//so all further terms are 0
      if(primesSquared[idx]*soFar > k)return 0;
//Otherwise, add the number of integers
//divisible by primesSquared[idx]*soFar to ret
      ret += (long long)(k/primesSquared[idx]/soFar);
//Then, add terms that don't include primesSquared[idx],
//but do include soFar and some other prime squared
      ret += recurse(idx+1,soFar,k);
//Finally, subtract terms that include
//both primesSquared[idx] and soFar and some other prime squared
      ret -= recurse(idx+1,soFar*primesSquared[idx],k);
      return ret;
   }

long long BS(long long N)
{
 long long I=1,F=(long long)1<<32;
 long long sol;
  while(I<=F)
 {
  long long piv=(I+F)/2LL;
  if(piv-recurse(1,1,piv)>=N)
  {
   F=piv-1;
   if(piv-recurse(1,1,piv)==N)
    sol=piv;
  }
  else
   if(piv-recurse(1,1,piv)<N)
    I=piv+1;
 }
 return sol;
}

int main()
{
 for(int i=2;i<=1000000;i++)
  if(!B[i])
  {
   primesSquared[++r]=(long long)i*i;
   if((long long)i*i>1000000LL)
    continue;
   for(int j=i*i;j<=1000000;j+=i)
    B[j]=1;
  }


 //si se quiere buscar el nth square free basta con buscar un m
 //tal que m-recurse(1,1,m)==n y se puede hacer con busqueda binaria

 long long N;
 cin >> N;

 cout << BS(N) << '\n';

}
