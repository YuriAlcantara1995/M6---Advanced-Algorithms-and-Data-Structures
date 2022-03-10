//para buscar maximo
typedef complex<ll> point;
typedef vector<point> hull;
ll cross(point a, point b){return imag(conj(a) * b);}
ll dot(point a, point b){ return real(conj(a) * b); }
void add(point a, hull &ch){
    for(int n = (int)ch.size(); n > 1 &&
        cross(ch[n-1]-ch[n-2], a-ch[n-2]) >= 0; n--)
            ch.pop_back();
    ch.push_back(a);
}
ll eval(point a, hull &ch){
    int lo = 0, hi = (int)ch.size()-1;
    while(lo < hi){
        int m = (lo + hi)/2;
        if( dot(ch[m], a) >= dot(ch[m+1], a) ) hi = m;
        else lo = m + 1;
    }
    return dot(ch[lo], a);
}
hull merge(const hull &a, const hull &b){
    int n =(int)a.size(), m =(int)b.size(), x=0, y=0;
    hull c;
    while(x < n && y < m){
        if(real(a[x]) <= real(b[y])) add(a[x++], c);
        else add(b[y++], c);
    }
    while (x < n) add(a[x++], c);
    while (y < m) add(b[y++], c);
    return c;
}
struct dyn{
    vector<hull> H;
    void add(point p){
        hull h; h.push_back(p);
        for (int i = 0; i < (int)H.size(); ++i){
            hull &ch = H[i];
            if (ch.empty()){ ch = h; return; }
            h = merge(h, ch);
            ch.clear();
        }
        if (!h.empty()) H.push_back(h);
    }
    ll query(point p){
        ll answer = -1ll<<60;
        for (int i = 0; i < (int)H.size(); ++i){
            hull &ch = H[i];
            if(ch.empty()) continue;
            answer = max( answer, eval(p, ch) );
        }
        return answer;
    }
};