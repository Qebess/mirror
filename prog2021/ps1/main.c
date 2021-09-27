#include <stdio.h>
#include <stdlib.h>
#include "playfair.h"
#include "bmp.h"

int main(){
	char *encrypted, *decrypted;

	// even length of string
	printf("part 1:\n");	
	encrypted = playfair_encrypt("smoothly", "adsorbing");
	printf("%s", encrypted);
	// "Hello world" --> "HELXLOVORLDX"
	printf("part 2:\n");
	// IS JZ JQ XN TK JC
	decrypted = playfair_decrypt("asdasd", encrypted);
	printf("%s", decrypted);
	printf("\n");
	// HELXLOVORLDX
	free(encrypted);
	free(decrypted);
	unsigned char *bmpE;
	char *bmpD;
	bmpE = bmp_encrypt("key","woodoo");
	for(int i = 0; bmpE[i];i++){
		printf("%x ",bmpE[i]);
	}
	printf("\n");
	bmpD = bmp_decrypt("key",bmpE);
	printf("%s\n",bmpD);
	free(bmpE);
	free(bmpD);


        return 0;
}

