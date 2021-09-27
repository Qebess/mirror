#include <stdio.h>

#include "bmp.h"
#include "transformations.h"

int main(){
	FILE* stream = fopen("file.bmp","rb");
	struct bmp_image* image = read_bmp(stream);
	if(image == NULL){
		printf("hi me!\n");
		return 1;
	}
	printf("POMOGITE MNE!");
	printf("size of image is %d\n", image->header->size);
	fclose(stream);
	struct bmp_image* image2 = flip_horizontally(image);
	stream = fopen("p2.bmp","wb");
	write_bmp(stream,image2);
	fclose(stream);
	struct bmp_image* image3 = flip_vertically(image);
	stream = fopen("p3.bmp","w");
	write_bmp(stream,image3);
	fclose(stream);
	struct bmp_image* image4 = rotate_right(image);
	stream = fopen("p4.bmp","wb");
	printf("size of image4 is %d\n", image4->header->size);

	write_bmp(stream,image4);
	fclose(stream);
	struct bmp_image* image5 = rotate_left(image);
	stream = fopen("p5.bmp","wb");
	write_bmp(stream,image5);
	fclose(stream);
	struct bmp_image* image6 = crop(image,0,0,96,128);
	stream = fopen("poc.bmp","wb");
	write_bmp(stream,image6);

	fclose(stream);
	image6 = scale(image,1.144472);
	stream = fopen("scale.bmp","w");
	write_bmp(stream,image6);
	fclose(stream);

	image6 = extract(image,"rg");
	stream = fopen("p8.bmp","wb");
	write_bmp(stream,image6);
	free_bmp_image(image);
	free_bmp_image(image2);
	free_bmp_image(image3);
	free_bmp_image(image4);
	free_bmp_image(image5);
	free_bmp_image(image6);
	return 0;
}
