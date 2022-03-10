#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
ordered_set X; //declaracion
X.insert(1); // insertar
X.erase( X.find( 2 ) ); //eliminar
cout<<*X.find_by_order(1)<<endl;// k-th menor elemento
cout<<X.order_of_key(-5)<<endl;//lower_bound(cant. de menores hay)