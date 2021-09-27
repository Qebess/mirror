#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "playfair.h"
char* playfair_encrypt(const char* key, const char* text);
char* playfair_decrypt(const char* key, const char* text);
char* copy(const char *str,const int count);


char* playfair_encrypt(const char* key, const char* text){
	if(key == NULL || text ==NULL ){
		return NULL;

	}

	if(strlen(key)==0 || strlen(text)==0){
		return NULL;
	}
	if(strlen(key)==1 && key[0]==' '){
		return NULL;
	}
	for(int i=0;key[i];i++){
		if(!isalpha(key[i]) && key[i] !=' '){
			return NULL;
		}
	}
	char  result[strlen(text)*2];
	for(int i = 0; text[i]; i++){
		result[i] = toupper(text[i]);
	}
	result[strlen(text)]='\0';
int n = 0;
	int j = 0;
// deleting spaces and w
	while(result[n] != '\0'){
		if(result[n] == ' '){
			for(j = n+1; result[j]; j++){
				result[j-1] = result[j];
			}
			result[j-1]='\0';
		}else if(result[n] == 'w' || result[n] == 'W') {
			result[n] = 'V';
		}else{
			n++;
		}
	}
	int count= 0;

//  count twiceletter
	for(int i=1;result[i];i++){
		if(result[i-1] == result[i]){
			count++;
		}
	}
//	adding X
	n =1;
	while(result[n]!='\0'){
		if(result[n-1] == result[n] && (result[n-1] != 'X') && 
		(n-1)%2 == 0){
			int l =strlen(result);
			for(int s = l-1; s>=n; s--){
				result[s+1] = result[s];
			}
			result[l+1] = '\0';

			result[n] = 'X';
			n+=2;
		}else{
			n++;
		}
	}
	if (strlen(result) %2 == 1){
		int ll =strlen(result);
		result[ll]  = 'X';
		result[ll+1]='\0';
	}
// end of foramting input word
	char key_cp[strlen(key)+26];
	for(int i = 0; key[i]; i++){
		key_cp[i] = toupper(key[i]);
		if(key_cp[i] =='W'){
			key_cp[i] = 'V';
		}
	}
	key_cp[strlen(key)]='\0';
	n = 1;
	j = 0;
	while(key_cp[n] != '\0'){
		if(key_cp[n] == ' '){
			for(j = n+1; key_cp[j]; j++){
				key_cp[j-1] = key_cp[j];
			}
			key_cp[j-1]='\0';
		}else{
			n++;
		}
	}
	strcat(key_cp,ALPHA);
	int changed =1;
	for(int i= 0; i<strlen(key_cp)-1; i++){
		while(changed ==1){
			changed=0 ;
			for(int j=i+1; j<strlen(key_cp); j++){
				if(key_cp[i] == key_cp[j]){
					changed =1;
					int k = 0;
					for(k = j; k< strlen(key_cp);k++){
						key_cp[k] = key_cp[k+1];
					}
				}
			}
		}
		changed =1;
	}
	
	char matrix[5][5];
	int d = 0;
	for(int i = 0;i<5; i++){
		for(int j = 0; j<5; j++){
			matrix[i][j] = key_cp[d];
			d++;
		}
	}
	d = 0;
	char pairs[strlen(result)/2][2];
	for(int i = 0; i<strlen(result)/2; i++){
		pairs[i][0] = result[d];
		d++;
		pairs[i][1] = result[d];
		d++;
	}
	int x1=0,x2=0,y1=0,y2=0;
	char a,b;
	for(int i = 0;i <strlen(result)/2; i++){
		a = pairs[i][0];
		b = pairs[i][1];
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				if(a == matrix[y][x]){
					x1 = x;
					y1 = y;
				}
				if(b == matrix[y][x]){
					x2 = x;
					y2 = y;
				}
			}
			if(x1 == x2){
				pairs[i][0] = matrix[(y1+1)%5][x1];
				pairs[i][1] = matrix[(y2+1)%5][x2];
			}else if(y1 == y2){
				pairs[i][0] = matrix[y1][(x1+1)%5];
				pairs[i][1] = matrix[y2][(x2+1)%5];
			}else{
				pairs[i][0] = matrix[y1][x2];
				pairs[i][1] = matrix[y2][x1];
			}
		}
	}
	
	char *ans = calloc(strlen(result)*2,sizeof(char));
	d = 0;
	for(int i = 0; i < strlen(result)/2  ; i++){
		ans[d] = pairs[i][0];
		d++;
		ans[d] = pairs[i][1];
		d++;
		ans[d] =' ';
		d++;
	}
	ans[strlen(ans)-1] = '\0';
//free matrix and pairs
	return ans;
}

char* playfair_decrypt(const char* key, const char* text){
	if((key == NULL) || (text ==NULL)|| strlen(key)==0 || (strlen(text)==0)){

		return NULL;
	}

	if(strlen(key)==1 && key[0]==' '){
		return NULL;
	}
	for(int i=0;key[i];i++){

		if(!isalpha(key[i]) && key[i] !=' '){

			return NULL;
		}
	}
	for(int i=0; text[i];i++){
		if(toupper(text[i])=='W'){
			return NULL;
		}
	}
	char key_cp[strlen(key)+26];
	for(int i = 0; key[i]; i++){
		key_cp[i] = toupper(key[i]);
		if(key_cp[i] == 'W'){
			key_cp[i] ='V';
		}
	}
	key_cp[strlen(key)] = '\0';
	int n = 1;
	int j = 0;
	while(key_cp[n] != '\0'){
		if(key_cp[n] == ' '){
			for(j = n+1; key_cp[j]; j++){
				key_cp[j-1] = key_cp[j];
			}
			key_cp[j-1]='\0';
		}else{
			n++;
		}
	}
	strcat(key_cp,ALPHA);
	int changed =1;
	for(int i= 0; i<strlen(key_cp)-1; i++){
		while(changed ==1){
			changed=0 ;
			for(int j=i+1; j<strlen(key_cp); j++){
				if(key_cp[i] == key_cp[j]){
					changed =1;
					int k = 0;
					for(k = j; k< strlen(key_cp);k++){
						key_cp[k] = key_cp[k+1];
					}
				}
			}
		}
		changed =1;
	}

	for(int i = strlen(key_cp)-1;!0;i--){
		if(key_cp[i]!=key_cp[i-1]){
			break;
		}else{
			key_cp[i]='\0';
		}
	}

	char matrix[5][5];
	int d = 0;
	for(int i = 0;i<5; i++){
		for(int j = 0; j<5; j++){
			matrix[i][j] = key_cp[d];
			d++;
		}
	}

	int count=0;
	for (int i = 0; text[i]; i++){
		if(text[i]!= ' '){
			count++;
		}
	}

	char pairs[count/2][2];
	int p =0;
	for(int i = 0; text[i]; i++){
		pairs[p][0] = text[i];
		i++;
		pairs[p][1] = text[i];
		p++;
		i++;
	}
	int x1=0,x2=0,y1=0,y2=0;
	char a,b;
		for(int i = 0;i <count/2; i++){
		a = pairs[i][0];
		b = pairs[i][1];
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				if(a == matrix[y][x]){
					x1 = x;
					y1 = y;
				}
				if(b == matrix[y][x]){
					x2 = x;
					y2 = y;
				}
			}
			if(x1 == x2){
				int ya = (y1-1)%5;
				int yb = (y2-1)%5;
				ya = (ya == -1) ? 4: ya;
				yb = (yb == -1) ? 4: yb;
				pairs[i][0] = matrix[ya][x1];
				pairs[i][1] = matrix[yb][x2];
			}else if(y1 == y2){
				int xa = (x1-1)%5;
				int xb = (x2-1)%5;
				xa = (xa == -1) ? 4:xa;
				xb = (xb == -1) ? 4:xb;
				pairs[i][0] = matrix[y1][xa];
				pairs[i][1] = matrix[y2][xb];
			}else{
				pairs[i][0] = matrix[y1][x2];
				pairs[i][1] = matrix[y2][x1];
			}
		}
	}
	char *ans = malloc(strlen(text)*sizeof(char));
	d =0;
	for(int i = 0; i< count/2; i++){
		ans[d] = pairs[i][0];
		d++;
		ans[d] = pairs[i][1];
		d++;
	}
	ans[d] ='\0';
	return ans;
}
