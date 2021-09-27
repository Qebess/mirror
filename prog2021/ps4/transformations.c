#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"
#include <string.h>
struct bmp_image* flip_horizontally(const struct bmp_image* image){
	if(image == NULL){
		return NULL;
	}
	struct bmp_image* result = calloc(1,sizeof(struct bmp_image));
	result->header = calloc(1,sizeof(struct bmp_header));
	*result->header = *image->header;
	uint32_t x = result->header->width;
	uint32_t y = result->header->height;
	struct pixel* pixel = calloc(x*y,sizeof(struct pixel));
	for(uint32_t i = 0; i< y;i++){
		for(uint32_t j = 0; j<x; j++){
			pixel[x*i+j].red = image->data[x*i+(x-j-1)].red;
			pixel[x*i+j].green = image->data[x*i+(x-j-1)].green;
			pixel[x*i+j].blue = image->data[x*i+(x-j-1)].blue;
		}
	}
	result->data = pixel;
	return result;
}
struct bmp_image* flip_vertically(const struct bmp_image* image){
	if(image==NULL){
		return NULL;
	}
	struct bmp_image* result = calloc(1,sizeof(struct bmp_image));
	result->header = calloc(1,sizeof(struct bmp_header));
	*result->header = *image->header;
	uint32_t x = result->header->width;
	uint32_t y = result->header->height;
	struct pixel* pixel = calloc(x*y,sizeof(struct pixel));
	for(uint32_t i = 0; i< y;i++){
		for(uint32_t j = 0; j<x; j++){
			pixel[x*i+j].red = image->data[x*(y-i-1)+j].red;
			pixel[x*i+j].green = image->data[x*(y-i-1)+j].green;
			pixel[x*i+j].blue = image->data[x*(y-i-1)+j].blue;
		}
	}
	result->data = pixel;
	return result;
}
struct bmp_image* rotate_left(const struct bmp_image* image){
	if(image==NULL){
		return NULL;
	}
	struct bmp_image* result = calloc(1,sizeof(struct bmp_image));
	result->header = calloc(1,sizeof(struct bmp_header));
	*result->header = *image->header;
	result->header->width = image->header->height;
	result->header->height = image->header->width;
	uint32_t x = result->header->width;
	uint32_t y = result->header->height;
	struct pixel* pixel = calloc(x*y,sizeof(struct pixel));

	uint32_t real =0;
	if(x*3%4 == 0){
		real = 0;
	}else{
		real = 4 - x*3%4;
	}
	result->header->image_size = (real+x*3)*y;
	result->header->size = result->header->image_size + result->header->offset;
	
	for(uint32_t i = 0; i< y;i++){
		for(uint32_t j = 0; j<x; j++){
			pixel[x*i+j].red = image->data[i+(x-j-1)*y].red;
			pixel[x*i+j].green = image->data[i+(x-j-1)*y].green;
			pixel[x*i+j].blue = image->data[i+(x-j-1)*y].blue;
		}
	}
	result->data = pixel;
	return result;
}
struct bmp_image* rotate_right(const struct bmp_image* image){
	if(image==NULL){
		return NULL;
	}
	struct bmp_image* result = calloc(1,sizeof(struct bmp_image));
	result->header = calloc(1,sizeof(struct bmp_header));
	*result->header = *image->header;
	result->header->width = image->header->height;
	result->header->height = image->header->width;
	uint32_t x = result->header->width;
	uint32_t y = result->header->height;

	uint32_t real =0;
	if(x*3%4 == 0){
		real = 0;
	}else{
		real = 4 - x*3%4;
	}
	result->header->image_size = (real+x*3)*y;
	result->header->size = result->header->image_size + result->header->offset;

	struct pixel* pixel = calloc(x*y,sizeof(struct pixel));
	for(uint32_t i = 0; i< y;i++){
		for(uint32_t j = 0; j<x; j++){
			pixel[x*i+j].red = image->data[(y-i-1)+j*y].red;
			pixel[x*i+j].green = image->data[(y-i-1)+j*y].green;
			pixel[x*i+j].blue = image->data[(y-i-1)+j*y].blue;
		}
	}
	result->data = pixel;
	return result;
}
struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
	if(image == NULL){
		return NULL;
	}
	if(image->header==NULL){
		return NULL;
	}
	if(image->data==NULL){
		return NULL;
	}
	if(start_y> image->header->height){
		return NULL;
	}
	if(start_x> image->header->width){
		return NULL;
	}
	if( height<1 || height > image->header->height){
		return NULL;
	}
	if( width<1 || width > image->header->width){
		return NULL;
	}
	uint32_t st_x = start_x;
	uint32_t st_y = image->header->height-height-start_y;
	if(st_x <0 || st_y<0 || st_x>image->header->width || st_y> image->header->height){
		return NULL;
	}
	struct bmp_image* new_image = calloc(1,sizeof(struct bmp_image));
	new_image->header = calloc(1,sizeof(struct bmp_header));
//	uint32_t x = image->header->width;
//	uint32_t y = image->header->height;
	*new_image->header = *image->header;
	new_image->header->width = width;
	new_image->header->height = height;
	new_image->header->image_size = width*height*3;
	new_image->header->size = new_image->header->image_size+new_image->header->offset;
	uint32_t xx= image->header->width;
//	uint32_t yy = image->header->height;
	uint32_t real =0;
	if(width*3%4 == 0){
		real = 0;
	}else{
		real = 4 - width*3%4;
	}
	new_image->header->image_size = (real+width*3)*height;
	new_image->header->size = new_image->header->image_size + new_image->header->offset;
	new_image->data = calloc((real+width)*height+1,sizeof(struct pixel));


	for(uint32_t i = 0; i< height; i++){
		for(uint32_t j = 0; j< width; j++){
			new_image->data[i*width+j].red 	= 	image->data[(i+st_y)*xx+j+st_x].red;
			new_image->data[i*width+j].green= 	image->data[(i+st_y)*xx+j+st_x].green;
			new_image->data[i*width+j].blue	= 	image->data[(i+st_y)*xx+j+st_x].blue;
		}
	}
	return new_image;
}
struct bmp_image* scale(const struct bmp_image* image, float factor){
	if(image==NULL){
		return NULL;
	}
	if(image->header == NULL){
		return NULL;
	}
	if(image->data == NULL){
		return NULL;
	}
	if(factor <= 0){
		return NULL;
	}
	uint32_t x = (uint32_t)round(image->header->width*factor);
	uint32_t y = (uint32_t)round(image->header->height*factor);
	struct bmp_image* result = calloc(1,sizeof(struct bmp_image));
	result->header = calloc(1,sizeof(struct bmp_header));
	*result->header = *image->header;
	result->header->width= x;
	result->header->height=y;
	uint32_t xx=  image->header->width;
	uint32_t yy=  image->header->height;
	result->header->image_size= x*y*3;
	result->header->size = result->header->image_size + result->header->offset;

	uint32_t real =0;
	if(x*3%4 == 0){
		real = 0;
	}else{
		real = 4 - x*3%4;
	}
	result->header->image_size = (real+x*3)*y;
	result->header->size = result->header->image_size + result->header->offset;
	result->data = calloc((real+x)*y+1,sizeof(struct pixel));


//	printf("factor = %f\n",((float)x/(float)xx) );
//	printf("x = %d , xx = %d\n", x,xx);
	float f_x = (float)x/(float)xx; 
	float f_y = (float)y/(float)yy;
	for(uint32_t i = 0; i<y; i++){
		for(uint32_t j = 0; j<x; j++){
			uint32_t pos = ((uint32_t)(i/f_y)*xx + (uint32_t)(j/f_x));
//			printf("pos %d to %d, %d , %d\n", pos, g, i,j);
			result->data[i*x+j].red =  image->data[pos].red;
			result->data[i*x+j].green = image->data[pos].green;
			result->data[i*x+j].blue = image->data[pos].blue;
		}
	}
//	asdsadasd
	return result; 
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
	if(image == NULL){
		return NULL;
	}
	if(image->header==NULL){
		return NULL;
	}
	if(image->data==NULL){
		return NULL;
	}
	if(colors_to_keep == NULL){
		return NULL;
	}
	if(strlen(colors_to_keep)==0){
		return NULL;
	}
	for(int i = 0 ; colors_to_keep[i]; i++){
		if(colors_to_keep[i]!= 'r' && colors_to_keep[i] != 'g' && colors_to_keep[i] !='b'){
			return NULL;
		}
	}
	bool r = 0;
	bool g = 0;
	bool b = 0;
	for(int i = 0; colors_to_keep[i]; i++){
		if(colors_to_keep[i]=='r'){
			r = 1;
		}
		if(colors_to_keep[i]=='g'){
			g = 1;
		}
		
		if(colors_to_keep[i]=='b'){
			b = 1;
		}
	}
	struct bmp_image* result = calloc(1,sizeof(struct bmp_image));
	result->header = calloc(1,sizeof(struct bmp_header));
	*result->header = *image->header;
	uint32_t x = image->header->width;
	uint32_t y = image->header->height;
	result->data = calloc(x*y,sizeof(struct pixel));

	for(uint32_t i = 0;i<y; i++){
		for(uint32_t j = 0 ; j <x ;j++){
			result->data[i*x+j].red = image->data[i*x+j].red;
			result->data[i*x+j].green = image->data[i*x+j].green;
			result->data[i*x+j].blue = image->data[i*x+j].blue;
			if(r==0){
				result->data[i*x+j].red = 0;
			}
			if(g==0){
				result->data[i*x+j].green = 0;
			}
			if(b==0){
				result->data[i*x+j].blue = 0;
			}
		}
	}
	return result;
}
