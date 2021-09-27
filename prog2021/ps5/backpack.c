#include "backpack.h"
#include <stdlib.h>
#include <stdio.h>

struct backpack* create_backpack(const int capacity){
    struct backpack* backpack = calloc(1, sizeof(struct backpack));
    backpack->capacity = capacity;
    backpack->size = 0;
    backpack->items = NULL;
    return backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack){
    backpack->items = destroy_containers(backpack->items);
    free(backpack);
    return NULL;
}
bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL){
        return false;
    }
    if(item == NULL){
        return false;   
    }
    if(backpack->capacity <= 0){
        return false;
    }
    if(backpack->size < 0 || backpack->size> backpack->capacity){
        return false;
    }
    if(backpack->capacity > backpack->size){
        if(backpack->items == NULL){
            backpack->items =  create_container(NULL,ITEM,item);
	 }else{
            create_container(backpack->items,ITEM,item);
        }
        backpack->size++;
        return true;
    }
    return false;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL){
        return;
    }
    if(item == NULL){
        return;
    }
    backpack->items = remove_container(backpack->items,item);
    backpack->size--;
}
struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if(backpack == NULL){
        return NULL;
    }
    if(name == NULL){
        return NULL;
    }
    return get_from_container_by_name(backpack->items,name);
}
