#include "game.h"

struct game* create_game(){
    struct game* game = calloc(1, sizeof(struct game));
    game->state = PLAYING;
    game->parser = create_parser();
    game->world = create_world();
    game->current_room = get_room(game->world,"spalna732");
    game->backpack = create_backpack(3);
    return game;
}
struct game* destroy_game(struct game* game){
    game->parser = destroy_parser(game->parser);

    game->world = destroy_world(game->world);

    game->current_room = NULL;

    game->backpack = destroy_backpack(game->backpack);

    free(game);
    return NULL;

}

void execute_command(struct game* game, struct command* command){
    if(strcmp(command->name,"KONIEC") == 0){
        game->state = GAMEOVER;
        return;
    }else if(strcmp(command->name,"SEVER") == 0){
        if(game->current_room->north != NULL){
            game->current_room = game->current_room->north;
        }
    }else if(strcmp(command->name,"JUH") == 0){
        if(game->current_room->south != NULL){
            game->current_room = game->current_room->south;
        }
    }else if(strcmp(command->name,"VYCHOD") == 0){
        if(game->current_room->east != NULL){
            game->current_room = game->current_room->east;
        }
    }else if(strcmp(command->name,"ZAPAD") == 0){
        if(game->current_room->west != NULL){
            game->current_room = game->current_room->west;
        }
    }else if(strcmp(command->name,"ROZHLIADNI SA") == 0){
        show_room(game->current_room);
    }else if(strcmp(command->name,"PRIKAZY") == 0){
        printf("\n\t\tHELPER\t\t\n");
        printf("------------------------------------\n");
        for(struct container* ptr = game->parser->commands; ptr!=NULL; ptr= ptr->next){
           printf("%s\t%s\n",ptr->command->name, ptr->command->description); 
        }
        struct container* ptr =  game->parser->history;
        for(; ptr->next != NULL; ptr= ptr->next);
        ptr = NULL;
    }else if(strcmp(command->name,"VERZIA") == 0){
        printf("%s\n",command->description);
        
        struct container* ptr =  game->parser->history;
        for(;ptr != NULL; ptr= ptr->next){
            if(ptr->next == NULL){
                break;
            }
            printf("%s\n",ptr->text);
        }
        if(ptr!= NULL){
            ptr = destroy_containers(ptr);
        }
    }else if(strcmp(command->name,"RESTART") == 0){
        game->state = RESTART;
        return;
    }else if(strcmp(command->name,"O HRE") == 0){
        printf("%s\n",command->description);
        struct container* ptr =  game->parser->history;
        for(; ptr->next != NULL; ptr= ptr->next);
        ptr = NULL;
    }else if(strcmp(command->name,"VEZMI") == 0){
        struct container* ptr = game->parser->history;
        for(;ptr->next != NULL; ptr = ptr->next);
        char *istr;
        istr = strstr(ptr->text,"VEZMI");
        if(istr != NULL){
            char item_name[128];
            int d = 0;
            for(long int i = istr - ptr->text+1+5;ptr->text[i];i++){
				if(ptr->text[i] != ' '){
               		item_name[d] =(char)tolower(ptr->text[i]);
                	d++;
                }
            }
            item_name[d] = '\0';
            printf("|%s|\n",item_name);
            struct item* item = get_item_from_room(game->current_room,item_name);
            if(item == NULL){
                printf("Neviem, čo chceš vziať.\n");
                struct container* ptr =  game->parser->history;
                for(; ptr->next != NULL; ptr= ptr->next);
                ptr = NULL;
                return;
            }
            if(item->properties % 2 == 0){
                printf("Predmet je ne MOVABLE\n");
                struct container* ptr =  game->parser->history;
                for(; ptr->next != NULL; ptr= ptr->next);
                ptr = NULL;
                return;
            }
            if(add_item_to_backpack(game->backpack,item)){
                delete_item_from_room(game->current_room,item);
            }else{
                printf("Nejake problemy so vzatim predmetov.");
                struct container* ptr =  game->parser->history;
                for(; ptr->next != NULL; ptr= ptr->next);
                ptr = NULL;
            }
        }
    }else if(strcmp(command->name,"POLOZ") == 0){
        struct container* ptr = game->parser->history;
        for(;ptr->next != NULL;ptr= ptr->next );
        char *istr;
        istr = strstr(ptr->text,"POLOZ");
        if(istr != NULL){
            char item_name[128];
            int d = 0;
            for(long int i = istr - ptr->text+1+5; ptr->text[i]; i++){
                item_name[d] = (char)tolower(ptr->text[i]);
                d++;
            }
            item_name[d] ='\n';
            struct item* item = get_item_from_backpack(game->backpack,item_name);
            if(item == NULL){
                printf("Neviem, čo chceš položiť");
                struct container* ptr =  game->parser->history;
                for(; ptr->next != NULL; ptr= ptr->next);
                ptr = NULL;
                return;
            }
            delete_item_from_backpack(game->backpack,item);
            add_item_to_room(game->current_room,item);
        }
    }else if(strcmp(command->name, "INVENTAR") == 0){
    	printf("NOW INVENTAR:\n");
		for(struct container* ptr = game->backpack->items; ptr;ptr = ptr->next){
			printf("\t%s\n",ptr->item->name);
		}
    }else if(strcmp(command->name,"POUZI") == 0){
        struct container* ptr = game->parser->history;
        for(;ptr->next != NULL;ptr= ptr->next );
        char *istr;
        istr = strstr(ptr->text,"POUZI");
        if(istr != NULL){
            char item_name[128];
            int d = 0;
            for(long int i = istr - ptr->text+1+5; ptr->text[i]; i++){
                item_name[d] = (char)tolower(ptr->text[i]);
                d++;
            }
            item_name[d] ='\n';
            struct item* item = get_item_from_backpack(game->backpack,item_name);
            if(item == NULL){
                printf("Neviem, čo chceš pouzit");
                struct container* ptr =  game->parser->history;
                for(; ptr->next != NULL; ptr= ptr->next);
                ptr = NULL;
                return;
            }
            if(item->properties %4 < 2){
                printf("Predmet ne je USABLE\n");
            }
            //struct item* item = get_item_from_room(game->current_room,item_name);
            return;
        }
    }else if(strcmp(command->name,"PRESKUMAJ") == 0){
        struct container* ptr = game->parser->history;
        for(;ptr->next != NULL;ptr= ptr->next );
        char *istr;
        istr = strstr(ptr->text,"PRESKUMAJ");
        if(istr != NULL){
            char item_name[128];
            int d = 0;
            for(long int i = istr - ptr->text+1+9; ptr->text[i]; i++){
                item_name[d] = (char)tolower(ptr->text[i]);
                d++;
            }
            item_name[d] ='\n';
            struct item* item = get_item_from_backpack(game->backpack,item_name);
            if(item == NULL){
                printf("Neviem, čo chceš preskamuvat.");
                struct container* ptr =  game->parser->history;
                for(; ptr->next != NULL; ptr= ptr->next);
                ptr = NULL;
                return;
            }
        }
    }else if(strcmp(command->name,"NAHRAJ") == 0){
        struct container* ptr = game->parser->history;
        for(;ptr->next != NULL;ptr= ptr->next );
        char *istr;
        istr = strstr(ptr->text,"NAHRAJ");
        if(istr != NULL){
            char path[128];
            int d = 0;
            for(long int i = istr - ptr->text+1+6; ptr->text[i]; i++){
                path[d] = (char)tolower(ptr->text[i]);
                d++;
            }
            path[d] ='\n';
            ptr = destroy_containers(ptr);
            FILE* load = fopen(path,"w");
            ptr = game->parser->history;
            for(;ptr!=NULL;ptr=ptr->next){
                fprintf(load,"%s\n",ptr->text);
            }
            fclose(load);
        }
    }else if(strcmp(command->name, "ULOZ") == 0){
        struct container* ptr = game->parser->history;
        for(;ptr->next != NULL;ptr= ptr->next );
        char *istr;
        istr = strstr(ptr->text,"uloz");
        if(istr != NULL){
            char path[128];
            int d = 0;
            for(long int i = istr - ptr->text+1+4; ptr->text[i]; i++){
                path[d] = (char)tolower(ptr->text[i]);
                d++;
            }
            path[d] ='\n';
            
            FILE* save = fopen(path,"r");
            if(save == NULL){
                printf("ERORR OPENING FILE.LOAD\n");
                return;
            }
            game = destroy_game(game);
            game = create_game();
            char buff[128];
            while(fscanf(save,"%s\n",buff) == 1){
                create_container(game->parser->history,TEXT,buff);
                struct command* com = parse_input(game->parser, buff);
                execute_command(game,com);
                command = destroy_command(com);
            }
            fclose(save);
        }
    }else{
        printf("command was not detected\n");
        struct container* ptr = game->parser->history;
        for(;ptr != NULL;ptr=ptr->next);
        ptr = destroy_containers(ptr);
        return;
    }
}

void play_game(struct game* game){
    while(game->state == PLAYING){
        char input[128];
        fgets(input,128*sizeof(char),stdin);
        for(int i = 0; input[i];i++ ){
            if(input[i] == '\n'){
                input[i] = '\0';
            }
			input[i] =(char)toupper(input[i]);
        }
        struct command* command = parse_input(game->parser,input);
        if(command != NULL){
            execute_command(game,command);
        }        
        if(game->state == GAMEOVER){
            return;
        }else if(game->state == SOLVED){
            return;
        }else if(game->state == RESTART){
            return;
        }
    }
}



