#include<cstdio>
#include<vector>
using namespace std;
const int INF = 1000 * 1000 * 1000;

int n;
vector <int> a[1003];
vector <int> xy, yx;
vector <char> vx, vy;
vector <int> minrow, mincol;
bool dotry (int i) {
    if (vx [i]) return false;
    vx [i] = true;
	 for (int j = 0; j <n; ++ j)
		 if (a [i][j]-minrow [i]-mincol [j] == 0)
			 vy [j] = true;
	 for (int j = 0; j <n; ++ j)
		 if (a [i][j]-minrow[i]-mincol[j] == 0 && yx[j] == -1) {
			 xy [i] = j;
			 yx [j] = i;
			 return true;
		 }
	 for (int j = 0; j <n; ++ j)
		 if (a[i][j]-minrow[i]-mincol[j] == 0 && dotry (yx[j])) {
			 xy[i] = j;
			 yx[j] = i;
			 return true;
		 }
		 return false;
}

void limpiar( )
{
    mincol.clear();
    minrow.clear();
    xy.clear();
    yx.clear();
    vx.clear();
    vy.clear();
}

int hungarian( )
{
     limpiar();

     mincol.assign (n, INF);
	 minrow.assign (n, INF);
	 for (int i = 0; i <n; ++ i)
		 for (int j = 0; j <n; ++ j)
			 minrow [i] = min (minrow[i], a [i][j]);
	 for (int j = 0; j <n; ++ j)
		 for (int i = 0; i <n; ++ i)
			 mincol [j] = min (mincol[j], a [i][j] - minrow[i]);


	 xy.assign (n, -1);
	 yx.assign (n, -1);
	 for (int c = 0; c <n;) {
		 vx.assign (n, 0);
		 vy.assign (n, 0);
		 int k = 0;
		 for (int i = 0; i <n; ++ i)
			 if (xy[i] == -1 && dotry (i))
				 ++k;
                  c += k;
		 if (k == 0) {
			 int z = INF;
			 for (int i = 0; i <n; ++ i)
				 if (vx [i])
					 for (int j = 0; j <n; ++ j)
						 if (!vy[j])
							 z = min (z, a[i][j]-minrow[i]-mincol[j]);
			 for (int i = 0; i <n; ++ i) {
				 if (vx[i]) minrow[i] += z;
				 if (vy[i]) mincol[i] -= z;
			 }
		 }
	 }

	 int ans = 0;
	 for (int i = 0; i <n; ++ i)
		 ans += a[i][xy[i]];
	 return ans;
}

int main () {

     scanf("%d",&n);

     int x;
     for( int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ )
           scanf("%d",&x), x *=-1 , a[i].push_back(x);

     printf("%d ",-hungarian());

     for( int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ )
            a[i][j] *= -1;
     printf("%d",hungarian());



}
