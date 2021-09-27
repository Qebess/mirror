#include "world.h"
#include <stddef.h>
struct container* create_world(){
    //0
    struct room* start_zone = create_room("spalna732","Hotelová spálňa 732.");
    //1
    struct room* coridor1 = create_room("сhodba1","Chodba");
    //2
    struct room* coridor2 = create_room("сhodba2","Chodba");    
    //3
    struct room* sklad = create_room("Sklad","Sklad s hodenou sekerou uprostred.");
    //4
    struct room* overlord = create_room("Izba s monitormi","Na stole sú kľúče.");
    //5
    struct room* coridor3 = create_room("сhodba3","Chodba");    
    //6
    struct room* coridor4 = create_room("сhodba4","Chodba so stenou, ktorá má malý otvor.");  
    //7
    struct room* end_win = create_room("safe zone","Safe zone.");  
    //8
    struct room* spalna1 = create_room("spalna742","Spalna so stenou, ktorá má malý otvor.");  
    //9
    struct room* coridor5 = create_room("сhodba5","Chodba");    
    //10
    struct room* spalna2 = create_room("spalna 755","Spálňa s rozbitou podlahou.");    
    //11
    struct room* coridor6 = create_room("сhodba6","Chodba");    
    //12
    struct room* coridor7 = create_room("сhodba7","Chodba");    
    //13
    struct room* coridor8 = create_room("сhodba8","Chodba");    
    //14
    struct room* coridor9 = create_room("сhodba9","Chodba");    
    //15
    struct room* coridor10 = create_room("сhodba10","Chodba");    
    //set_exits_from_room(room, north,south, east, west)
    set_exits_from_room(start_zone,NULL,NULL,coridor1,NULL);
    set_exits_from_room(coridor1,NULL,NULL,coridor2,start_zone);
    set_exits_from_room(coridor2,coridor4,NULL,sklad,coridor1);
    set_exits_from_room(sklad,NULL,NULL,NULL,coridor2);
    set_exits_from_room(overlord,NULL,NULL,coridor3,NULL);
    set_exits_from_room(coridor3,coridor5,NULL,coridor4,overlord);
    set_exits_from_room(coridor4,NULL,coridor2,NULL,NULL);
    set_exits_from_room(end_win,coridor6,NULL,NULL,NULL);
    set_exits_from_room(spalna1,coridor7,NULL,coridor5,NULL);
    set_exits_from_room(coridor5,NULL,coridor3,NULL,spalna1);
    set_exits_from_room(spalna2,coridor9,NULL,NULL,NULL);
    set_exits_from_room(coridor6,coridor10,end_win,NULL,NULL);
    set_exits_from_room(coridor7,NULL,spalna1,coridor8,NULL);
    set_exits_from_room(coridor8,NULL,NULL,coridor9,coridor7);
    set_exits_from_room(coridor9,NULL,spalna2,coridor10,coridor8);
    set_exits_from_room(coridor10,NULL,coridor6,NULL,coridor8);



    struct item* axe = create_item("axe","An axe for destroing weak wall.",MOVABLE | USABLE);
    add_item_to_room(sklad,axe);
    struct item* key = create_item("kluc","Kluc podlia dveri.",MOVABLE | USABLE);
    add_item_to_room(overlord,key);
    struct item* touch = create_item("touch","Touch... could be usable in dark rooms",MOVABLE | USABLE);
    add_item_to_room(coridor8,touch);
    struct item* phone = create_item("phone","Help u to escape from this hotel.",MOVABLE|USABLE);
    add_item_to_room(spalna2,phone);
    struct item* hole = create_item("hole", "Just a hole in floor",OPENABLE);
    add_item_to_room(spalna2,hole);
    struct item* exit = create_item("exit","Win the game.",USABLE);
    add_item_to_room(end_win,exit);

    struct container* world = create_container(NULL,ROOM,start_zone);
    add_room_to_world(world,coridor1);
    add_room_to_world(world,coridor2);
    add_room_to_world(world,sklad);
    add_room_to_world(world,overlord);
    add_room_to_world(world,coridor3);
    add_room_to_world(world,coridor4);
    add_room_to_world(world,end_win);
    add_room_to_world(world,spalna1);
    add_room_to_world(world,coridor5);
    add_room_to_world(world,spalna2);
    add_room_to_world(world,coridor6);
    add_room_to_world(world,coridor7);
    add_room_to_world(world,coridor8);
    add_room_to_world(world,coridor9);
    add_room_to_world(world,coridor10);

    return world;
}
struct container* add_room_to_world(struct container* world, struct room* room){
	if(room == NULL){
		return NULL;
	}
	if(world == NULL){
		return  create_container(NULL,ROOM,room);
	}
	if(get_room(world,room->name) ==  NULL){
	    return create_container(world,ROOM,room);
	}else{
		return NULL;
	}
}
struct container* destroy_world(struct container* world){
    return destroy_containers(world);
}
struct room* get_room(struct container* world, char* name){
    return get_from_container_by_name(world,name);
}
