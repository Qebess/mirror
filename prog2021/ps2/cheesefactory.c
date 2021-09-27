#include <stdio.h>
#include <math.h>

#define PI 3.14159265359
#define VK 1000000
typedef long double LD;

LD formulaO(LD r, LD a ,LD b){

	LD ans = PI*((b-a)*r*r -pow(b,3)/3+pow(a,3)/3);
	return ans;
}

LD formula(LD start ,LD end,int m ,LD  g[m][6]){
	int numb[m];
	LD a = start;
	LD b = end;
	for(int i =0;i<m;i++){
		numb[i]=0;
	}
	for(int i = 0; i<m; i++){
		if((g[i][4]<=a && a<=g[i][5]) || (g[i][4]<=b &&b<=g[i][5]) || (a<=g[i][4] && g[i][4]<=b) ){
			numb[i] =1;
		}
	}
	LD sum=0;
	for(int i = 0; i<m; i++){
		a = start;
		b = end;
		if(numb[i]==1){
			if(a<=g[i][3]){
				if(a<=g[i][4]){
					a = -g[i][0];
				}else{
					a = a - g[i][3];
				}
			}else{
				a = a-g[i][3];
			}
			if(b>=g[i][3]){
				if(b>=g[i][5]){
					b = g[i][0];
				}else{
					b = b -g[i][3];
				}
			}else{
				b =  b - g[i][3];
			}
			sum+=formulaO(g[i][0],a,b);
		}
	}
	LD v = (LD)10000*(end-start) - sum;
	return v;
}
int main(){
	int m,s;
	scanf("%d %d", &m,&s);
	if(s==0){
		printf("%.9f",100.0);
		return 0;
	}
	LD g[m][6];
	for(int i =0;i<m; i++){
		scanf("%Lf %Lf %Lf %Lf", &g[i][0], &g[i][1], &g[i][2], &g[i][3]);
		g[i][0]/=1000;
		g[i][1]/=1000;
		g[i][2]/=1000;
		g[i][3]/=1000;
		g[i][4]= g[i][3] - g[i][0];
		g[i][5]= g[i][3] + g[i][0];

	}
	LD sum =0;
	for(int i = 0; i<m; i++){
		sum+= (LD)4/3*PI*pow(g[i][0],3);
	}
	LD rez = VK -sum;
	LD weight  = rez/s;
	for(int i = 0; i<m-1; i++){
		for(int j = i+1; j<m; j++){
			if(g[i][3]>g[j][3]){
				for(int k = 0;k<6;k++){
					LD buff = g[j][k];
					g[j][k] = g[i][k];
					g[i][k] = buff;
				}
			}
		}
	}
	LD w = weight;
	LD slice[s][2];
	for(int i = 0; i<s;i++){
		slice[i][0] = 0;
		slice[i][1] = 1;
	}
	for(int i = 0; i<s-1;i++){
		while(1){
			int did = 0;
			LD t = formula(slice[i][0],slice[i][1],m,g);
			if(w-0.0000001<=t && t<=w+0.0000001){
				slice[i+1][1] = slice[i][1]+1;
				slice[i+1][0] = slice[i][1];
				did = 1;
				break;
			}else if(t>w){
				LD diff = 0.5;
				while(1){
					if(t>w){
						slice[i][1]-=diff;
						diff/=2;
					}else if(t<w){
						slice[i][1]+=diff;
						diff/=2;
					}
					if(diff == 0){
						slice[i+1][1]=slice[i][1]+1;
						slice[i+1][0]=slice[i][1];
						did = 1;
						break;
					}
					t = formula(slice[i][0],slice[i][1],m,g);
					if(w-0.000001<=t && t<=w+0.0000001){
						slice[i+1][1]=slice[i][1]+1;
						slice[i+1][0]=slice[i][1];
						did = 1;

						break;
					}
				}
			}
			if(did){
				break;
			}
			slice[i][1]++;
		}
	}
	slice[s-1][1] = 100;
	for(int i = 0; i<s-1; i++){
		slice[i][1] -= slice[i][0];
	}
	for(int i = 0; i<s-1;i++){
		printf("%.9Lf\n",slice[i][1]);
	}
	slice[s-1][1]-= slice[s-1][0];
	printf("%.9Lf\n",slice[s-1][1]);
	
	return 0;
}
