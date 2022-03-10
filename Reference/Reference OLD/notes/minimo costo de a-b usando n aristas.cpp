//calcular en un grafo el menor costo de ir de un nodo A a un nodo B usando exactamente N aristas
//idea
//construir una matrix de adyacencia poniendo el costo de la arista y si no existe poniendo infinito
//modificar la multiplicacion de matrices por lo siguiente
//AB[i][j] = inf;					  N	
//entonces AB[i][j] = min( AB[i][j], min( A[i][k]+B[k][j] ) )
//									 k=1	