#include <iostream>
#include <climits>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

#define BSIZE 1<<15
using namespace std;
 
int A,B,C,D;
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
 
long readLong() 
{
	long d = 0L, x = 0L;
	char c;
	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c=='-') {return -1;}
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}

long long f(long long* sums,int x,int y){
	long long sum=sums[y]-sums[x-1];
	return ((A*(sum*sum))+(B*sum)+C);
}



void solve(long long *sums,int N,bool*plates){
	long long* M=(long long*)malloc(sizeof(long long)*(N+1));
	//long long sum=0;
unsigned long long result=0;	
	long long max ;
	M[0]=0;
	int l=1,k;
	plates[0]=true;
	for (int i=1;i<=N;i++){
		max=LLONG_MIN;
		for (int j=i;j>=1;j--){
			k=j;
			if (M[j-1]+f(sums,j,i)>=max){
				
				max=M[j-1]+f(sums,j,i);
				l=j;
				}
			if (plates[j-1]){k--;break;}
		}
		if (f(sums,k,i)>max){
			l=k;
		}
		for (int z=l;z<=i;z++){M[z]=f(sums,l,z);plates[z]=false;}
		plates[l]=true;
	}
	for (int i=1;i<N;i++){
		if(plates[i+1]){result+=M[i];cout <<"+ "<<M[i]<<" = "<<result<<"\n";}
	}
	result+=M[N];
    cout << result<<"\n";
}

int main(int argc,char* argv[]){
	long N=readLong();
	A=readLong();
	if (A==-1){A=(-1)*readLong();}
	B=readLong();
	if (B==-1){B=(-1)*readLong();}
	C=readLong();
	if (C==-1){C=(-1)*readLong();}
	long temp;
	long long* sums=(long long*)malloc(sizeof(long long)*(N+1));
	bool* plates=(bool*)malloc(N+1);
	sums[0]=0;
	for (int i=1;i<=N;i++){
		temp=readLong();
		sums[i]=sums[i-1]+temp;
		plates[i]=true;
	}
   
	D=(-B)/(float)(2*A);
	solve(sums,N,plates);

    return 0;
}
