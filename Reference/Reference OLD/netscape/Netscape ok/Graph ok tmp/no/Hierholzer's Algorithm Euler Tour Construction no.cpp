//Hierholzer's Algorithm (Euler Tour Construction) ( O(E+V) ).
void findEulerTour(int s){
    for (int i = 1; i <= n && deg[s] > 0; i++){
      if (!G[s][i]) continue;
      deledge(s,i); // delete edge(s,i) y (i,s)
      findEulerTour(i);
    }
    C[cp++]=s; 
}
