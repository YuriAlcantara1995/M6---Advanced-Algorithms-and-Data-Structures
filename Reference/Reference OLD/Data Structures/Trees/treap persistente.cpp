#include <bits/stdc++.h>
using namespace std;
#define le first
#define ri second


const int maxn = 100005;

struct nodo{
    int val, sz;
    nodo *l, *r;
    nodo(){
        val = 0;
        sz = 1;
        l = r = nullptr;
    }
}*root;//lista de versiones del treap; Importante recalcar que en una implementacion de una estructura persistente
//nunca se modifica una version, sino se crea otra con la modificacion

int sz( nodo *x ){
    if( !x )return 0;
    return x->sz;
}

void updsz( nodo *x ){
    if( !x )return;
    x->sz = sz(x->l) + sz(x->r) + 1;
}

int A[maxn], T, I1[maxn], F1[maxn], I2[maxn], F2[maxn];
nodo *trash[3000006];
typedef pair<nodo*,nodo*>par;
nodo *merge( nodo *l, nodo *r ){//mezcla dos treaps en uno
    if( !l )return r;
    if( !r )return l;
    int tl = sz(l), tr = sz(r);
    nodo *ret = new nodo();//nodo copia que va a contener el treap resultante del merge
    trash[++T] = ret;
    if( rand()%(tl+tr) < tl ){//(talla de probabilidades que no entiendo),
        ret->val = l->val;//si el nodo de la izquierda tiene mas prioridad, entonces es la raiz y su hijo izquierdo
        ret->l = l->l;  //se convierte en el hijo izquierdo de la nueva version
        ret->r = merge(l->r,r);//en cambio el derecho es la mezcla del drecho del root y el arbol r
    }else{
        ret->val = r->val;//aqui lo mismo pero al reves
        ret->r = r->r;
        ret->l = merge(l,r->l);
    }
    updsz(ret);
    return ret;
}

par split( nodo *root, int k ){//retorna a 2 treaps, el primero contiene los k primeros elementos y el segundo los demas
    if( !root ) return par(root,root);
    nodo *ret = new nodo();
    trash[++T] = ret;
    ret->val = root->val;//copio el valor de root
    if( sz(root->l)+1 <= k ){//si la cant de elementos en left+1 <= k es decir que este pedazo pertenece a la solucion
        par x = split(root->r,k-sz(root->l)-1);//calculamos el otro pedazo
        ret->l = root->l;//entonces el nodo actual va a tener left = al left de root y rigth = a left del split
        ret->r = x.le;
        updsz(ret);
        return par(ret,x.ri);//retorno los elementos que sirven y los que no
    }else{//en caso que este nodo no sirva su copia tampoco
        par x = split(root->l,k);//calculo el pedazo que me sirve de la izquierda
        ret->r = root->r;//el nodo actual no me sirve y lo igualo al derecho del root que no me sirve y
        ret->l = x.ri;//al que no me sirve del que me retorne.
        updsz(ret);
        return par(x.le,ret);//retono lo que me sirve y no me sirve
    }
}


int N, M;
void crear( ){
    root = nullptr;
    for( int i = 1; i <= N; i++ ){
        nodo *n = new nodo();
        trash[++T] = n;
        n->val = A[i];
        n->sz = 1;
        root = merge(root,n);
    }
}

int C;
void recover( nodo *cur ){
    if( !cur )return;
    recover(cur->l);
    A[++C] = cur->val;
    recover(cur->r);
}

void print(){
    for( int i = 1; i <= N; i++ ){
            cout << A[i];
            if( i != N )
                cout << ' ';
        }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    #ifdef home
    freopen("a.in","r",stdin);
    #endif // acm
    srand(0);
    cin >> N >> M;
    for( int i = 1; i <= N; i++ ){
        A[i] = i;
    }

    crear();

    int k, a, b;
    for( int i = 1; i <= M; i++ ){
        cin >> k >> a >> b;
        I2[i] = a, F2[i] = k;
        I1[i] = b, F1[i] = k;
    }


    nodo *p1, *p2, *p3;
    for( int i = M; i >= 1; i-- ){
        par x = split(root,I1[i]-1);
        p1 = x.le, p2 = x.ri;
        x = split(p2,F1[i]);
        p3 = x.le;//1 pedazo valido;
        x = split(root,I2[i]-1);
        p1 = x.le, p2 = x.ri;
        x = split(p2,F2[i]);
        p2 = x.ri;
        root = merge(p1,p3);
        root = merge(root,p2);
        if( T > 2500000 ){
            C = 0;
            recover(root);
            for( int j = 1; j <= T; j++ )
                trash[j]->l = trash[j]->r = nullptr;
            for( int j = 1; j <= T; j++ )
                delete trash[j];
            T = 0;
            crear();
        }
    }

    C = 0;
    recover(root);
    print();


    return 0;
}
