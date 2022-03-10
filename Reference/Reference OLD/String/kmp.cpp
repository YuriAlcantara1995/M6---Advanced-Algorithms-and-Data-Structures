/// KMP, busca P en T
void pre_kmp( ){
 for(int j = 0, i = 2; i <= tp; i ++){
  while( j && P[j + 1] != P[i]) j = fall[j];
  if(P[j + 1] == P[i]) j ++;
  fall[i] = j;
 }
}
void kmp(  ){
 for(int j = 0, i = 1; i <= tt; i ++){
  while( j && P[j + 1] != T[i]) j = fall[j];
  if(P[j + 1] == T[i]) j ++;
  if(j == tp) printf("%d\n", i - tp + 1);
 }
}