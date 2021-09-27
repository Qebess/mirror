#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include<string.h>

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if(name == NULL){
        return NULL;
    }
    if(description == NULL){
        return NULL;
    }
    if(strlen(name) == 0){
        return NULL;
    }
    if(strlen(description) ==  0){
        return NULL;
    }
    struct command* command = calloc(1,sizeof(struct command));
	if(pattern != NULL){
	    int err;
	    err = regcomp(&command->preg,pattern,REG_ICASE);
	    if(err){
	        regfree(&command->preg);
	        free(command);
	        return NULL;
	    }
	}
    command->name = malloc(strlen(name)+1);
    strcpy(command->name,name);
    command->description = malloc(strlen(description)+1);
    strcpy(command->description,description);
    command->nmatch = nmatch;
    command->groups = NULL;
    return command;
}
struct command* destroy_command(struct command* command){
	if(command == NULL){
		return NULL;
	}
	if(&command->preg != NULL){
    	regfree(&command->preg);
    }

    if(command->name != NULL){
        free(command->name);
    }
    if(command->description != NULL){
        free(command->description);
    }

    if(command->groups != NULL){
        free(command->groups);
    }
	if(command){
    	free(command);
    }
    return NULL;   
}
