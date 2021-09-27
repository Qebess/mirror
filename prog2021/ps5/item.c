#include "item.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct item* create_item(char* name, char* description, unsigned int properties){
	if(name == NULL){
		return NULL;
	}
	if(strlen(name)==0){
		return NULL;
	}
	if(description == NULL){
		return NULL;
	}
	if(strlen(description) == 0){
		return NULL;
	}
	if(properties >15){
		return NULL;
	}
	struct item* item = calloc(1,sizeof(struct item));
	item->name = malloc(strlen(description)+1);
	strcpy(item->name,name);
	item->description = malloc(strlen(description)+1);
	strcpy(item->description,description);
	item->properties = properties;
	return item;
}
struct item* destroy_item(struct item* item){
	if(item == NULL){
		return NULL;
	}
	if(item->name != NULL){
		free(item->name);
	}
	if(item->description != NULL){
		free(item->description);
	}
	free(item);
	return NULL;
}
