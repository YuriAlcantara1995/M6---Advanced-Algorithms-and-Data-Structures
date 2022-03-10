FIBONACCI LOG N
//* This run O(log n) time//
long conquer_fibonacci(long n){
	long i,h,j,k,t;
	i=h=1;
	j=k=0;
	while(n>0){
		if(n%2==1){
			t=j*h;
			j=i*h + j*k +t;
			i=i*k + t;
		}
	t=h*h;
	h=2*k*h + t;
	k=k*k + t;
	n=(long) n/2;
	}
	return j;
}

int main(){
	long n,res;
	while(scanf("%ld",&n)==1){
		res=conquer_fibonacci(n);
		printf("%ld\n",res);
	}
return 0;
}