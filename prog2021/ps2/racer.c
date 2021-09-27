#include <stdio.h>
#include <stdbool.h>
#include <math.h>
typedef long double LD;

LD edge(int n,int p[n][2], LD x){
	LD s = 0;
	for(int i=0; i<n; i++){
		if(x+p[i][1]==0){
			return -1;
		}
		s+=(LD)p[i][0]/(x+p[i][1]);
	}
	return s;
}

int main(){
	int n,t;
	scanf("%d %d",&n,&t);
	int p[n][2];
	for(int i=0;i<n;i++){
		scanf("%d %d", &p[i][0],&p[i][1]);
	}
	int min = 1000;
	for(int i = 0; i<n;i++){
		if(min>p[i][1]){
			min = p[i][1];
		}
	}
	LD x=-min;
	LD edge1;

	while(1){
		edge1 = edge(n,p,x);
		if(edge1 != -1){
			if(edge1 == t){
				printf("%.9Lf",x);
				return 0;
			}else if(edge1<t){
				break;
			}
		}
		x++;
		if(x>10000){
			printf("Hate myself\n");
			return 0;
		}
	}
	LD diff = 0.5;
	LD copy_x = x;
	while(1){
		if(edge1<t){
			x-=diff;
			diff/=2;
		}else if(edge1>t){
			x+=diff;
			diff/=2;
		}
		edge1 = edge(n,p,x);
		if(diff == 0){
			printf("%.9Lf",copy_x);
			return 0;
		}
		if(fabs(t-edge1) <= 0.0001*t && t>1000 ){
			printf("%.9Lf",x+0.0000001);
			return 0;
		}
		if(edge1 == -1){
			printf("%.9Lf",x+0.0000001);
			return 0;
		}
		if((LD)t-0.000000001 <= edge1 && edge1 <=(LD)t+0.000000001){
				printf("%.9Lf",x);
				return 0;
		}
	}
	return 0;
}
