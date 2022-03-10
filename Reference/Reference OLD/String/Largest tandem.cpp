// Longest Square
void bfail(char *l,int n,char *r,int m){ //fail[i] guarda el mayor sufijo de l, que es sufijo para la posición i en r
int it=0;
for(int i=n-1;i>=0;i--) temp[it++]=l[i]; //invierte las dos cadenas y las concatena
for(int i=m-1;i>=0;i--) temp[it++]=r[i];
    Zfunction(temp,it);
for(int i=0;i<m;i++) fail[i]=min(z[m+n-i-1],n);
}

void sqfind(char *s1,int l1,char *s2,int l2){ //encuentra los cuadrados de la concatenación de l2 y
    bfail(s1,l1,s2,l2);						// l1  centrados en l2 o entre las dos cadenas, que abarcan a l1
Zfunction(s2,l2);
for(int i=l2-1;i>resz;i--)
if(z[i]+fail[i-1]>=i) //implica que hay un cuadrado centrado entre i e i-1
            resz=max(resz,i);
for(int i=l2-1;i>=resz;i--) //implica que hay un cuadrado entre
if(fail[i]>=i+1)	//implica que hay un cuadrado entre l1 y l2;
resz=max(resz,i+1);
}
void lsquare(char *txt,int len){
if(len==1) return;
if(len==2){
        resz=max(resz,int(txt[0]==txt[1]));
return;
    }
int n=len/2,m=len-len/2;
char *s1=txt,*s2=txt+n;
    lsquare(s1,n);
    lsquare(s2,m);
    sqfind(s1,n,s2,m);
    reverse(s1,s1+n);reverse(s2,s2+m);
    sqfind(s2,m,s1,n);
    reverse(s1,s1+n);reverse(s2,s2+m);
}
