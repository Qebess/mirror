#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
	int sum= 0;
	int d;
	while(1){
		d = getchar();
		if(d=='\n'){
			printf("%d\n",sum);
			return 0;
		}else{
			sum+=(d-48);
			if(sum>9){
				sum = sum%10 + sum/10;
			}
		}
	}
	return 0;
}
