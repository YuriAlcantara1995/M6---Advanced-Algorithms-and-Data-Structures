struct LiChao_max{
	struct line	{
        int a, b;
        line() { a = 0; b = 0; }
        line(int _a, int _b) { a = _a; b = _b; }
        int64_t eval(int x) { return a * 1ll * x + (int64_t)b; }
	};
	struct node	{
        node *l, *r; line f;
        node() { f = line(); l = nullptr; r = nullptr; }
        node(int a,int b){f=line(a,b);l=nullptr;r=nullptr;}
        node(line v) { f = v; l = nullptr; r = nullptr; }
	};
	typedef node* pnode;
	pnode root; int sz;
    void init(int _sz) { sz = _sz + 1; root = nullptr; }
    void add_line(int a, int b) { 
		line v = line(a, b); insert(v, -sz, sz, root); 
	}
    int64_t query(int x) { return query(x, -sz, sz, root); }
    void insert(line &v, int l, int r, pnode &nd){
        if(!nd) { nd = new node(v); return; }
        int64_t trl = nd->f.eval(l), trr = nd->f.eval(r);
        int64_t vl = v.eval(l), vr = v.eval(r);
		int mid = (l + r) >> 1;

		//max
        if(trl >= vl && trr >= vr) return;
        if(trl < vl && trr < vr){nd->f=v;return;}
        if(trl < vl) swap(nd->f, v);
        if(nd->f.eval(mid) > v.eval(mid))
		     insert(v, mid+1, r,nd->r);
        else swap(nd->f, v), insert(v, l, mid, nd->l);
		
		/* min
		if(trl <= vl && trr <= vr) return;
        if(trl > vl && trr > vr) { nd->f = v; return; }
        if(trl > vl) swap(nd->f, v);
        if(nd->f.eval(mid) < v.eval(mid)) 
		     insert(v, mid + 1, r, nd->r);
        else swap(nd->f, v), insert(v, l, mid, nd->l); */
    }
    int64_t query(int x, int l, int r, pnode &nd){
        if(!nd) return -inf; //min-> inf
        if(l == r) return nd->f.eval(x);

        int mid = (l + r) >> 1;
        if(mid >= x) //min
		    return max(nd->f.eval(x), query(x, l, mid, nd->l));
        return max(nd->f.eval(x), query(x, mid + 1, r, nd->r));
    }
};
