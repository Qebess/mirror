#include "room.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct room* create_room(char *name, char *description){
	if(name == NULL ){
		return NULL;
	}
	if(strlen(name) == 0){
		return NULL;
	}

	if(description == NULL){
		return NULL;
	}
	if(strlen(description) == 0){
		return NULL;
	}
	struct room* room = calloc(1,sizeof(struct room));
	room->name = malloc(strlen(name)+1);
	strcpy(room->name,name);
	room->description = malloc(strlen(description)+1);
	strcpy(room->description,description);
	room->items =  NULL;
	room->north = NULL;
	room->south = NULL;
	room->east = NULL;
	room->west = NULL;
	room->items = NULL;
	return room;
}
struct room* destroy_room(struct room* room){
	if(room == NULL){
		return NULL;
	}
	room->north = NULL;
	room->south = NULL;
	room->east = NULL;
	room->west = NULL;
	if(room->name != NULL){
		free(room->name);
	}
	if(room->description != NULL){
		free(room->description);
	}
	if(room->items != NULL){
		room->items = destroy_containers(room->items);
	}
	free(room);
	return NULL;
}
void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
	if(room == NULL){
		return ;
	}
	room->north = north;
	room->south = south;
	room->east = east;
	room->west = west;
}
void show_room(const struct room* room){
	if(room == NULL){
		return;
	}
	printf("%s\n",room->description);
	printf("Mozne vychody z miesnosti:\n");
	if(room->north != NULL){
		printf("\tsever\n");
	}	
	if(room->south != NULL){
		printf("\tjuh\n");
	}	
	if(room->east != NULL){
		printf("\tvychod\n");
	}	
	if(room->west != NULL){
		printf("\tzapad\n");
	}
	printf("Vidíš:\n");
	if(room->items == NULL){
		return;
	}
	printf("not NULL\n");
	struct container* ptr = room->items;
	while(ptr!=NULL){
		printf("\t%s\n",ptr->item->name);
		ptr=ptr->next;
	}	
}
void delete_item_from_room(struct room* room, struct item* item){
	room->items = remove_container(room->items,item);
}
void add_item_to_room(struct room* room, struct item* item){
	if(room == NULL){
		return;
	}
	if(room->items == NULL){
		room->items = create_container(NULL,ITEM,item);
		return;
	}
	create_container(room->items,ITEM,item);
	
	
}
struct item* get_item_from_room(const struct room* room, const char* name){
	if(room == NULL){
		return NULL;
	}
	if(name == NULL){
		return NULL;
	}
	if(strlen(name) == 0){
		return NULL;
	}
	return get_from_container_by_name(room->items,name);
	return NULL;
}

