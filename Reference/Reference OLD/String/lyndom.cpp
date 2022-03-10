Dada una string s devuelve la Lyndon decomposition en tiempo lineal usando el algo-
ritmo de Duval. Factoriza s como s 1 s 2 ...s k con s 1 = s 2 = ··· = s k y tal que s i es
Lyndon, esto es, es su menor rotacin.
Obtener la mnima rotacin de s: en la descomposicin de Lyndon de s 2 es el ltimo i < |s|
con el que empieza una Lyndon.
string s; // input string
 int n = (int) s. length ();
 int i = 0;
 while (i <n) {
	 int j = i + 1, k = i;
	 while (j <n & & s [k] <= s [j]) {
		 if (s [k] <s [j])
			 k = i;
		 else
			 + + K;
		 + + J;
	 }
	 while (i <= k) {
		 cout <<s. substr (i, j - k) <<'';
		 i + = j - k;
	 }
 } 