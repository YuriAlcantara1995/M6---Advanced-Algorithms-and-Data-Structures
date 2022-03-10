Ternary Search

double TS()
{ 
 double left = 0, right = (double)maxi;

 while(right-left > EPS)
 {
  double lt = (2.*left + right) / 3;
  double rt = (left + 2.*right) / 3;
  if(f(lt) > f(rt))//minimo (< si maximo)
   left = lt;
  else
   right = rt;
 }

 return (left+right)/2;
}