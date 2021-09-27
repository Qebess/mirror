#include <stdio.h>
#include <stdlib.h>
#include "container.h"
#include <string.h>
#include <ctype.h>

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(entry == NULL){
        return NULL;
    }
    if(type >3 || type <0){
        return NULL;
    }
    if(first != NULL){
        if(type != first->type){
            return NULL;
        }
    }
    struct container* cont = calloc(1,sizeof(struct container));
    if(type == ROOM){
        cont->type = ROOM;
        cont->room = (struct room*)entry;
    }else if(type == ITEM){
        cont->type = ITEM;
        cont->item = (struct item*)entry;
    }else if(type == COMMAND){
        cont->type = COMMAND;
        cont->command =(struct command*)entry;
    }else if(type == TEXT){
        cont->type = TEXT;
        if(strlen((char*)entry) >0){
		cont->text =(char*) entry;
        }else{
            free(cont);
            return NULL;
        }
    }
    cont->next = NULL;
    if(first == NULL){
        first = cont;
    }else{
        struct container* ptr = first;
        for(;ptr->next;ptr=ptr->next);
        ptr->next = cont;
    }
        return cont;
}


struct container* destroy_containers(struct container* first){
	if(first == NULL){
		return NULL;
	}
	if(first->next != NULL){
		destroy_containers(first->next);
	}
	if(first->type == ROOM){
		first->room = destroy_room(first->room);
	}else if(first->type == ITEM){
		first->item = destroy_item(first->item);
	}else if(first->type == COMMAND){
		first->command = destroy_command(first->command);
	}
	first->next = NULL;
	free(first);
	return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name){
	if(first == NULL){
		return NULL;
	}
	if(name == NULL){
		return NULL;
	}
	if(strlen(name) == 0){
		return NULL;
	}
	if(first->type == ROOM){
		if(strlen(name) == strlen(first->room->name)){
			bool ind = 1;
			for(int i = 0; name[i]; i++){
				if(tolower(name[i])!=first->room->name[i]){
					ind = 0;
				}
			}
			if(ind == 1){
				return first->room;
			}else{
				if(first->next == NULL){
					return NULL;
				}else{
					return get_from_container_by_name(first->next,name);
				}
			}
		}else{
			if(first->next == NULL){
				return NULL;
			}else{
				return get_from_container_by_name(first->next,name);
			}
		}
	}else if(first->type == ITEM){
		if(strlen(name) == strlen(first->item->name)){
			bool ind = 1;
			for(int i = 0; name[i]; i++){
				if(tolower(name[i])!=first->item->name[i]){
					ind = 0;
				}
			}
			if(ind == 1){
				return first->item;
			}else{
				if(first->next == NULL){
					return NULL;
				}else{
					return get_from_container_by_name(first->next,name);
				}
			}
		}else{
			if(first->next == NULL){
				return NULL;
			}else{
				return get_from_container_by_name(first->next,name);
			}
		}

	}else if(first->type == COMMAND){
		if(strlen(name) == strlen(first->command->name)){
			bool ind = 1;
			for(int i = 0; name[i]; i++){
				if(tolower(name[i])!=first->command->name[i]){
					ind = 0;
				}
			}
			if(ind == 1){
				return first->command;
			}else{
				if(first->next == NULL){
					return NULL;
				}else{
					return get_from_container_by_name(first->next,name);
				}
			}
		}else{
			if(first->next == NULL){
				return NULL;
			}else{
				return get_from_container_by_name(first->next,name);
			}
		}
	}else if(first->type == TEXT){
		if(strstr(first->text,name) == NULL){
			if(first->next == NULL){
				return NULL;
			}else{
				return get_from_container_by_name(first->next,name);
			}
		}else{
			return first->text;
		}
	}
	return NULL;
}

struct container* remove_container(struct container *first, void *entry){
	if(first == NULL){
		return NULL;
	}
	if(entry == NULL){
		return first;
	}
	if(first->type == ROOM){
		struct room* ent = (struct room*)entry;
		if(first == NULL){
			return NULL;
		}
		struct container* ptr = first;
		while(ptr!=NULL){
			if(strcmp(ptr->room->name,ent->name)==0 ){
				while(ptr->next!=NULL){
					struct room* buff = ptr->room;
					ptr->room = ptr->next->room;
					ptr->next->room = buff;
					ptr = ptr->next;
				}
				ptr = destroy_containers(ptr);
				ptr = NULL;
				return first;
			}
			ptr = ptr->next;
		}
		return first;
	}else if(first->type == ITEM){
		struct item* ent = (struct item*)entry;
		if(first == NULL){
			return NULL;
		}
		struct container* ptr = first;
		while(ptr!=NULL){
			if(strcmp(ptr->item->name,ent->name) == 0){
				while(ptr->next!=NULL){
					struct item* buff = ptr->item;
					ptr->item = ptr->next->item;
					ptr->next->item = buff;
					ptr = ptr->next;
				}
				ptr = destroy_containers(ptr);
				ptr = NULL;
				return first;
			}
			ptr = ptr->next;
		}
		return first;
	}else if(first->type == COMMAND){
		struct command* ent = (struct command*)entry;
		if(first == NULL){
			return NULL;
		}
		struct container* ptr = first;
		while(ptr!=NULL){
			if(strcmp(ptr->command->name,ent->name)==0){
				while(ptr->next!=NULL){
					struct command* buff = ptr->command;
					ptr->command = ptr->next->command;
					ptr->next->command = buff;
					ptr = ptr->next;
				}
				ptr = destroy_containers(ptr);
				ptr =NULL;
				return first;
			}
			ptr = ptr->next;
		}
		return first;
	}else if(first->type == TEXT){
		if(first == NULL){
			return NULL;
		}
		struct container* ptr = first;
		while(ptr!=NULL){
			if(strcmp(ptr->text,entry)==0){
				while(ptr->next!=NULL){
					char* buff = ptr->text;
					ptr->text = ptr->next->text;
					ptr->next->text = buff;
					ptr = ptr->next;
				}
				ptr = destroy_containers(ptr);
				ptr = NULL;
				return first;
			}
			ptr = ptr->next;
		}
		return first;
	}
	return NULL;
}

