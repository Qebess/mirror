#include <stdio.h>

int is_ananas(const char ananas[], const char buffer[]){
	for(int j = 0; j<6 ; j++){
		if(!(ananas[j] == buffer[j] || ananas[j]-32 == buffer[j])){
			return 0;
			break;
		}
	}
	return 1;
}
int main(int argc, char* argv[]){
	FILE *fp = fopen(argv[1
],"r");

	if(fp ==NULL){
		fclose(fp);
		fp = fopen(argv[1],"w");
		fputc('0',fp);
		fclose(fp);
		return 0;
	}
	char ananas[] ="ananas",buffer[7];
	int i = 0,count = 0;
	char ch = fgetc(fp);
	buffer[i] = ch;
	i++;
	buffer[6] ='\0';
	for(int i = 0; i<6; i++){
		buffer[i] = fgetc(fp);
	}
	if(is_ananas(ananas,buffer)){
		count++;
	}
	while(ch != EOF){
		for(int k = 0; k<5;k++){
			buffer[k] =buffer[k+1];
		}
		ch = fgetc(fp);
		buffer[5] = ch;


		if(is_ananas(ananas,buffer)){
			count++;
		}
		
	}
	fclose(fp);
	fp = fopen(argv[1],"w");
	if(count > 9){
		char numb[16];
		int i=0;
		while(count){
			numb[i]= (count % 10 )+48;
			count = count /10;
			i++;
		}
		for(int k = i -1; k>-1; k--){
			fputc(numb[k],fp);
		}
		fclose(fp);
	}else{
		fputc(count +48,fp);
		fclose(fp);
	}

	return 0;
}
