(<) --> lower_bound
(<=) --> upper_bound
#include <cstdio>
#include <algorithm>
#define RANG 100
using namespace std;
int n, m, up, N[RANG], SOL[RANG], ID[RANG], L[RANG];
void write (int ID) {
	if (ID) {
		write (L[ID]);
		printf ("%d ", N[ID]);
	}
}
int main() {
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf ("%d", &N[i]);
	for (int i = 1; i <= n; i++) {
		if (SOL[m] <= N[i]) {
			SOL[++m] = N[i];
			ID[m] = i;
			L[i] = ID[m - 1];
		}
		else {
			up = upper_bound (SOL + 1, SOL + m + 1, N[i]) - SOL;
			SOL[up] = N[i];
			ID[up] = i;
			L[i] = ID[up - 1];
		}
	}
	printf ("%d\n", m);
	write (ID[m]);
	return 0;
}