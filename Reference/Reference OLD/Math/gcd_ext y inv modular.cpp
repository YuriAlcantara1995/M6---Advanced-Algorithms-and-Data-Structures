GCD Extendido
ll GCDext(ll a, ll b, ll &x, ll &y){
   ll g = a; x = 1 ; y = 0;
   if (b != 0){
      g = GCDext(b, a % b, y, x);
      y -= (a / b) * x;
   }
   return g;
}
Inverso Modular
ll invMod(ll a, ll m, ll &inv) {
   ll x, y;
   if (GCDext(a, m, x, y) != 1) 
	   return 0 ; // noSolucion
   inv = (x + m) % m;
   return 1;
}
