#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"


char* reverse(const char* text);
char* vigenere_encrypt(const char* key, const char* text);
char* vigenere_decrypt(const char* key, const char*text);
unsigned char* bit_encrypt(const char* text);
char *bit_decrypt(const unsigned char* text);
unsigned char *bmp_encrypt(const char* key, const char* text);
char* bmp_decrypt(const char* key, const unsigned char* text);

char* reverse(const char* text){
	if(text == NULL){
		return NULL;
	}
	char *rev = calloc(strlen(text)+1, sizeof(char));
	for(int i =0; text[i]; i++){
		rev[i] = toupper(text[strlen(text)-1-i]);
	}
	return rev;
}
#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
char* vigenere_encrypt(const char* key, const char* text){
	if(key == NULL || strlen(key) == 0|| text == NULL || strlen(text) == 0){
		return NULL;
	}
	for(int i =0; key[i];i++){
		if(!isalpha(key[i])){
			return NULL;
		}
	}
	char *alph = ALPHA;
	char *k = calloc(strlen(text)+1,sizeof(char));
	int d = 0;
	for(int i = 0; text[i]; i++){
		if(text[i] == ' '){
			k[i] = ' ';
		}else{
			k[i] = toupper(key[d]);
			d++;
		}
		if(d == strlen(key)){
			d = 0;
		}
	}
	int pos1,pos2,rez;
	char *ans = calloc(strlen(text) +1 , sizeof(char));
	for(int i = 0; text[i]; i++){
		pos1 =-1;
		pos2 =-1;
		for(int pos = 0; alph[pos]; pos++){
			if(toupper(text[i]) == alph[pos]){
				pos1 = pos;
				break;
			}
		}
		if(pos1 == -1){
			ans[i] = text[i];
			continue;
		}
		for(int pos = 0; alph[pos]; pos++){
			if(k[i] == alph[pos]){
				pos2 =pos;
				break;
			}
		}
		rez = (pos1 + pos2) % strlen(alph);
		ans[i] = alph[rez];
	}
	free(k);
	return ans;
}
char* vigenere_decrypt(const char* key, const char*text){
	if(key == NULL || strlen(key) == 0|| text == NULL || strlen(text) == 0){
		return NULL;
	}
	for(int i =0; key[i];i++){
		if(!isalpha(key[i])){
			return NULL;
		}
	}
	char *alph = ALPHA;
	char *k = calloc(strlen(text)+1,sizeof(char));
	int d = 0;
	for(int i =0; text[i]; i++){
		if(text[i] == ' '){
			k[i] = ' ';
		}else{
			k[i] = toupper(key[d]);
			d++;
		}
		if(d == strlen(key)){
			d=0;
		}
	}
	int pos1,pos2,rez;
	char *ans = calloc(strlen(text) +1 , sizeof(char));
	for(int i = 0; text[i]; i++){
		pos1 =-1;
		pos2 =-1;
		for(int pos = 0; alph[pos]; pos++){
			if(text[i] == alph[pos]){
				pos1 = pos;
				break;
			}
		}
		if(pos1 == -1 ){
			ans[i] = text[i];
			continue;
		}
		for(int pos = 0; alph[pos]; pos++){
			if(k[i] == alph[pos]){
				pos2 =pos;
				break;
			}
		}
		rez = (pos1 - pos2 + strlen(alph)) % strlen(alph);
		ans[i] = alph[rez];
	}
	free(k);
	
	return ans;
}
unsigned char* bit_encrypt(const char* text){
	if(text == NULL || strlen(text)==0){
		return NULL;
	}
	void swap(int *a,int *b){
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
	unsigned char *ans = calloc(strlen(text)+1, sizeof(char));
	for(int s =0; text[s]; s++){	
		char h = text[s];
		int hint = h;
		int bit[8] ={0,0,0,0,0,0,0,0};
		for(int i = 7; i>=0; i--){
			bit[i] = hint % 2;
			hint = hint / 2; 
		}
		

		swap(&bit[0],&bit[1]);
		swap(&bit[2],&bit[3]);
		
		bit[4] = bit[0]^bit[4];
		bit[5] = bit[1]^bit[5];
		bit[6] = bit[2]^bit[6];
		bit[7] = bit[3]^bit[7];
	
		int g = 128*bit[0]+
				64*bit[1]+
				32*bit[2]+
				16*bit[3]+
				8*bit[4]+
				4*bit[5]+
				2*bit[6]+
				1*bit[7];
		ans[s] = (char)g;
	
	}		
	return ans;
	
}
char* bit_decrypt(const unsigned char* text){
	if(text == NULL){
		return NULL;
	}
	int m=0;
	for(;text[m];m++);
	if(m==0){
		return NULL;
	}
	void swap(int *a,int *b){
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
	int l = 0;
	for(;text[l];l++);
	char *ans = calloc(l+1,sizeof(char));
	for(int s =0; text[s]; s++){	
		unsigned char h = text[s];
		int hint = h;
		int bit[8] ={0,0,0,0,0,0,0,0};
		for(int i = 7; i>=0; i--){
			bit[i] = hint % 2;
			hint = hint / 2; 
		}

		bit[4] = bit[0]^bit[4];
		bit[5] = bit[1]^bit[5];
		bit[6] = bit[2]^bit[6];
		bit[7] = bit[3]^bit[7];
	
		swap(&bit[0],&bit[1]);
		swap(&bit[2],&bit[3]);

		int g = 128*bit[0]+
				64*bit[1]+
				32*bit[2]+
				16*bit[3]+
				8*bit[4]+
				4*bit[5]+
				2*bit[6]+
				1*bit[7];
		ans[s] = g;
	}		

	return ans;	 
}
unsigned char *bmp_encrypt(const char* key, const char* text){
	if(key == NULL || strlen(key) == 0|| text == NULL || strlen(text) == 0){
		return NULL;
	}
	for(int i =0; key[i];i++){
		if(!isalpha(key[i])){
			return NULL;
		}
	}
	char *rev = reverse(text);
	char *vin = vigenere_encrypt(key,rev);
	free(rev);
	unsigned char *bit = bit_encrypt(vin);
	free(vin);
	
	return bit;
}

char* bmp_decrypt(const char* key, const unsigned char* text){
	if(key == NULL || strlen(key) == 0|| text == NULL ){
		return NULL;
	}
	int m = 0;
	for(;text[m];m++);
	if(m==0){
		return NULL;
	}
	for(int i =0; key[i];i++){
		if(!isalpha(key[i])){
			return NULL;
		}
	}
	

	char *bit = bit_decrypt(text);
	char *vin = vigenere_decrypt(key,bit);
	free(bit);
	char *rev = reverse(vin);
	free(vin);

	return rev;

}
