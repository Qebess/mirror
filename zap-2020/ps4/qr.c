#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
void encode_char(const char character, bool bits[8]){
	int letter =(int)character;
	for(int i = 7;  i>=0; i--){
		bits[i] = letter % 2;
		letter /=2;
	}
}

char decode_byte(const bool bits[8]){
	char letter =(128*bits[0]+64*bits[1]+32*bits[2]+16*bits[3]+8*bits[4]+4*bits[5]+2*bits[6]+1*bits[7]);
	return letter;
}
void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
	int i;
	for(i = 0; string[i]; i++){
		encode_char(string[i],bytes[i]);
	}
	encode_char(string[i],bytes[i]);
}
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
	for(int i = 0; i <rows;i++){
		string[i] = decode_byte(bytes[i]);
	}
}
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
	for(int i =0;i<cols;i++){
		for(int j = 0; j<offset*8; j++){
			blocks[j][i]=0;
		}
	}
	for(int i = 0; i< rows; i++){
		for(int j =0;j<8;j++){
			blocks[j + 8*(i/cols) ][i%cols] = bytes[i][j];
		}
	}
}


void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
	for(int i= 0;i<rows; i++){
		for(int j = 0;j<8;j++){
			bytes[i][j] = blocks[j + 8*(i/cols)][i%cols];
		}
	}

}
int main(){return 0;}

