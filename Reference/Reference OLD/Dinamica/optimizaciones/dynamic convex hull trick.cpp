const ll INF=1ll<<60;

struct Line{
    	long long a, b;
    	Line(long long a = 0, long long b = INF): a(a), b(b) {}//-INF para maximo
    	long long getval(long long x) {
    		return a*x + b;
    	}
    };

    struct Node{
    	int l, r;
    	Line line;
    	Node *left, *right;

    	Node(int l, int r): l(l), r(r), line(), left(NULL), right(NULL) {}

    	void Push() {
    		if (l < r && !left) {
    			left = new Node(l, (l + r)/2);
    			right = new Node((l + r)/2 + 1, r);
    		}
    	}

    	void update(Line L) {
    		Push();
    		Line A = line, B = L;
    		if (A.getval(l) < B.getval(l)) swap(A,B); // > para maximo
    		if (A.getval(r) >= B.getval(r)) line = B; // <= para maximo
    		else if (l != r) {
    			int mid = (l + r)/2;
    			if (A.getval(mid) < B.getval(mid)) {// > para maximo
    				line = A;
    				left -> update(B);
    			} else {
    				line = B;
    				right -> update(A);
    			}
    		}
    	}

    	long long get(int x) {
    		long long ans = line.getval(x);
    		int mid = (l + r)/2;
    		if (x <= mid && left) ans = min(ans, left -> get(x));// max para maximo
    		if (x > mid && right) ans = min(ans, right -> get(x));// max para maximo
    		return ans;
    	}
    }*CHT;
	
	CHT= new Node(-MAXX,MAXX);