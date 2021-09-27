#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hof.h"

int load( struct player list[] ){
	FILE  *fp =  fopen("score","r");

	if(fp == NULL){
		fp = fopen("score","w");
		fclose(fp);
		return -1;
	}
	char name[30],score[6];
	char ch;
	ch = (char)fgetc(fp);
	name[0] = ch;
	int i = 0;
	int count = 0;
	while(ch != EOF){
		while(ch != ' ' && ch !=EOF && ch !='\n'){
			name[i] = ch;
			i++;
			ch = (char)fgetc(fp);

		}
		ch = (char)fgetc(fp);
		name[i] = '\0';

		i = 0;
		while(ch != '\n' && ch !=EOF){
			score[i] = ch;
			i++;
			ch = (char)fgetc(fp);
		}
		ch = (char)fgetc(fp);
		score[i] = '\0';
		i = 0;
		strcpy(list[count].name,name);
		sscanf(score,"%d",&list[count].score);
		count++;
	}
	fclose(fp);
	for(int i = 0 ; i < count-1; i++){
		for(int j = i+1; j < count; j++){
			
			if(list[i].score <= list[j].score){
				int buf = 0;
				buf = list[i].score;
				list[i].score = list[j].score;
				list[j].score = buf;
				char bm[100] = "";
				strcat(bm,list[i].name);
				strcpy(list[i].name,list[j].name);
				strcpy(list[j].name,bm);
			}
		}
	}
	return count;
}
bool save(const struct player list[],const int size){
	FILE *fp = fopen("score","w");
	for(int i = 0; i<size; i++){
		fprintf(fp,"%s %d\n", list[i].name, list[i].score);
	}
	fclose(fp);
	return 1;
}
bool add_player(struct player list[], int *size, const struct player player){
	bool ok = false;
	if(*size == 0){
		list[0].score = player.score;
		strcpy(list[0].name,player.name);
		*size = *size+1;
		return true;
	}
	if((list[*size-1].score > player.score)  && (*size < 10)){
		strcpy(list[*size].name,player.name);
		list[*size].score = player.score;
		*size = *size +1;
		return true;
	}

	if(*size <10){
		*size = *size +1;
	}
	for(int i = 0; i < *size ; i++){
		if(list[i].score <= player.score){
			for(int j = *size -2; j >= i; j--){
				list[j+1].score =  list[j].score;
				strcpy(list[j+1].name,list[j].name);
			}
			list[i].score = player.score;
			strcpy(list[i].name,player.name);
			ok = true;
			break;
		}
	}
	
	return ok;
}
//int main(){
//	struct player player = {.name="Sue", .score=2};
//	int size=0;
//	struct player hof[10];
//	printf("%d \n",add_player(hof,&size,player));
//	for(int i = 0; i<size; i++){
//		printf("%s %d\n", hof[i].name, hof[i].score);
//	}
//	return 0;
//}

 
