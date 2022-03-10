typedef long long ll;

//Para minimo
//Las pendientes deben entrar en orden decreciente

struct line{
    ll m, n;
    inline ll y( ll x ){
        return m*x+n;
    }
};

struct cht{
    vector<line>hull;
    int pt;
    cht(){
        pt = 0;
    }
    inline bool is_bad( line a, line b, line c ){
        return (b.n-a.n)*(a.m-c.m) >= (c.n-a.n)*(a.m-b.m);
    }

    inline void update( line a ){
        int sz = hull.size();
        while( sz >= 2 && is_bad(hull[sz-2],hull[sz-1],a) )
            hull.pop_back(), sz--;
        hull.push_back(a);
    }
    inline ll query( ll x ){
        if( pt > (int)hull.size()-1 )
            pt = hull.size()-1;
        while( pt < (int)hull.size()-1 && hull[pt].y(x) >= hull[pt+1].y(x) )
            pt++;
        return hull[pt].y(x);
    }
};

//Para Maximo
//Las pendientes deben entrar en orden creciente

struct convex_hull_trick {
    vector< pair<double,double> > h;
    double intersect(int i) {
        return (h[i+1].second-h[i].second)/(h[i].first-h[i+1].first);
    }
    void add(double m, double b) {
        h.push_back(make_pair(m,b));
        while (h.size() >= 3) {
            int n = h.size();
            if (intersect(n-3) < intersect(n-2)) break;
            swap(h[n-2], h[n-1]);
            h.pop_back();
        }
    }
    double get_max(double x) {
        int lo = 0, hi = h.size() - 2, res = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (intersect(mid) <= x) res = mid, lo = mid + 1;
            else hi = mid - 1;
        }
        return h[res+1].first*x + h[res+1].second;
    }
   void clear()
   {
    h.clear();
   }
}CHT;