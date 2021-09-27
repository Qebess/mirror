#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

struct bmp_header* read_bmp_header(FILE* stream){
	if(stream == NULL){
		return NULL;
	}
	fseek(stream, 0, SEEK_SET);

	struct bmp_header* header = calloc(1,sizeof(struct bmp_header));
	bool ok = fread(header, sizeof(struct bmp_header), 1, stream);

	if(ok != 1){
		free(header);
		return NULL;
	}
	if(header->offset != 54){
		free(header);
		return NULL;
	}
	if(header->dib_size != 40){
		free(header);
		return NULL;
	}
	if(header->bpp != 24){
		free(header);
		return NULL;
	}
	if(header->type!= 0x4d42){
		free(header);
		return NULL;
	}
	if(header->width < 0){
		free(header);
		return NULL;
	}
	if(header->height < 0){
		free(header);
		return NULL;
	}
	return header;
}
struct pixel* read_data(FILE* stream, const struct bmp_header* header){
	if(stream == NULL){
		return NULL;
	}
	if(header == NULL){
		return NULL;
	}
	uint32_t x = header->width;
	uint32_t y = header->height;
	uint32_t real = header->width%4;
	struct pixel* pixel = calloc(x*y,sizeof(struct pixel));
	int g = 0;
	fseek(stream, sizeof(struct bmp_header),0);
	for(uint32_t i = 0; i<y; i++){
		for(uint32_t j = 0; j<x; j++){
			fread(&pixel[g], sizeof(struct pixel), 1, stream);
			g=g+1;
		}
		fseek(stream, real, SEEK_CUR);
	}
	return pixel;
}

struct bmp_image* read_bmp(FILE* stream){
	if(stream == NULL){
		return NULL;
	}
	struct bmp_image* image = calloc(1,sizeof(struct bmp_image));

	image->header = read_bmp_header(stream);
	if(image->header == NULL){
		free(image);
		fprintf(stderr,"Error: This is not a BMP file.\n");
		return NULL;
	}
	image->data = read_data(stream,image->header);
	if(image->data ==NULL){
		fprintf(stderr,"Error: Corrupted BMP file.\n");
		free(image->header);
		free(image);
		return NULL;
	}
	return image;

}
bool write_bmp(FILE* stream, const struct bmp_image* image){
	if(image == NULL){
		return false;
	}
	if(image->header == NULL){
		return false;
	}
	if(image->data == NULL){
		return false;
	}
	fwrite(image -> header, sizeof(struct bmp_header),1,stream);

	uint32_t y = image->header->height;
	uint32_t x = image->header->width;

	unsigned char space[3] = {'\0', '\0', '\0'};
	for (uint32_t i = 0; i < y; i++){
		for(uint32_t j = 0;j < x; j++){
			fwrite(&image->data[(i*x)+j],sizeof(struct pixel),1,stream);
		}

		for(int k = 0; k<x%4; k++){
			fwrite(space, sizeof(unsigned char), 1,stream);

		}
	}
	return true;
}
void free_bmp_image(struct bmp_image* image){
    if(image!=NULL){
	    free(image->header);
    	free(image->data);
        free(image);

    }
}
