//Cantidad de permutaciones de 1-n tal que ningun elemento caiga en su posicion
d(0)=1, d(1) = 0, d(2) = 1
d(n) = (n-1)*(d(n-1) + d(n-2))
