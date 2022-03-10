#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define maxn 100005

using namespace std;
using namespace __gnu_pbds;

typedef tree < int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > Tr;
Tr T;

/**
- Funciona Como un set no como multiset, para repetir elementos, llevar un par en vez de un int donde el .second sea el
  id y para usar las funciones utilizar ej order_of_key(par(x,1<<30));
- Las funciones:
  insert(key), find(key), erase(key), erase(*it)
  find_by_order(k)->deveulve un puntero con el k-esimo menor elemento comenzando desde 0
  order_of_key(key)->devulve la cantidad de elementos que son estrictamente menores que key
**/

int main()
{


    return 0;
}
