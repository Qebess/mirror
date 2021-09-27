#include <stdio.h>

int is_start(const char word[]){
	char start[] = "START";
	for(int i = 0; start[i]; i++){
		if(word[i] != start[i]){
			return 0;
		}
	}
	return 1;
}
int is_stop(const char word[]){
	char stop[] = "STOP";
	for(int i = 0; i<4; i++){
		if(word[i] != stop[i]){
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[]){
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
    if(input == NULL){
        fclose(input);
        fclose(output);

        return 0;
    }
	char word[15];
	int i = 1;

	char ch = fgetc(input);
	word[0] = ch;
	while(ch != EOF){
		ch = fgetc(input);
		if(i<5){
			word[i] = ch;
			word[i+1] ='\0';
			i++;
		}else{
		
			if(is_start(word)){
				int len =0;
				ch = fgetc(input);
                int flag=0;
				while(ch != EOF){
					do{
						ch = fgetc(input);
						word[len] = ch;
						len++;
					}while(ch != ' ' && ch != EOF);
					word[len] ='\0';
					len = 0;
					if(is_stop(word)){
						break;
					}
					do{
						ch = fgetc(input);
						word[len] = ch;
						len++;
					}while(ch != ' ' && ch!=EOF);
					word[len-1] ='\0';
					len =0;
					if(is_stop(word)){
						break;
					}
                    if(flag){
                        fputc(' ',output);                    
                    }
					for(int d = 0; word[d]; d++){
						fputc(word[d],output);
					}
                    flag=1;

				}
			}
			for(int k = 0; k<4; k++){
				word[k] = word[k+1];
			}
			word[4] = ch;
			word[5] = '\0';
		}

	}
	fclose(input);
	fclose(output);
	return 0;
}