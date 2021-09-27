#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void menu();
void end_menu();
void start_game();
int pow_10(int i){
    if(i == 1){
    	return 1;
    }else{
    	int  d = 10*pow_10(i-1);
    	return d;
    }
}
int atoi(const char *numb){
	int  i = 0;
    int number=0;
    for(; numb[i]; i++);
    int len =i;
    for(;i!=0;i--){
	    number += (numb[len - i]-48)*pow_10(i);
	}
    return number;
}
void init(){
	initscr();
	savetty();
	nonl();
	cbreak();
	noecho();
	timeout(0);
	curs_set(0);
	leaveok(stdscr, TRUE);
}
void finish(){
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
	exit(0);
}
void make_zone_of_game(char lvl[]){
clear();

 mvprintw(0,0,"  Score:     lvl:%s  ",lvl);
 mvprintw(1,0,"  +++++++++++++++++++++ ");
 mvprintw(2,0,"  |    |    |    |    | ");
 mvprintw(3,0,"  |    |    |    |    | ");
 mvprintw(4,0,"  |    |    |    |    | ");
 mvprintw(5,0,"  |    |    |    |    | ");
 mvprintw(6,0,"  |    |    |    |    | ");
 mvprintw(7,0,"  |    |    |    |    | ");
 mvprintw(8,0,"  |    |    |    |    | ");
 mvprintw(9,0,"  |    |    |    |    | ");
mvprintw(10,0,"  |    |    |    |    | ");
mvprintw(11,0,"  |    |    |    |    | ");
mvprintw(12,0,"  |    |    |    |    | ");
mvprintw(13,0,"  |    |    |    |    | ");
mvprintw(14,0,"  |    |    |    |    | ");
mvprintw(15,0,"  |    |    |    |    | ");
mvprintw(16,0,"  |    |    |    |    | ");
mvprintw(17,0,"  |----|----|----|----| ");
mvprintw(18,0,"  |----|----|----|----| ");
mvprintw(19,0,"  | D  | F  | K  | L  | ");
mvprintw(20,0,"  +++++++++++++++++++++ ");
	refresh();
}
//Static varible
#define LINES_OF_BOARD 14
static int score = 0;
static int combo = 0;
int size_map(int map[][4]){
	int i = 0;
	for(; map[i][0] != 7;i++);
	return i;
}

void check_d(const int i, int map[][4]){
	attron(COLOR_PAIR(4));
	mvprintw(19,3,"====");
	attroff(COLOR_PAIR(4));
	refresh();
	int sizeOfMap=size_map(map);
	if(i>LINES_OF_BOARD && i<sizeOfMap){
		if(map[i-LINES_OF_BOARD-2][0]){
			attron(COLOR_PAIR(3));
			mvprintw(19,3,"@@@@");
			attroff(COLOR_PAIR(3));
			combo++;
			score +=5;
		}else{
			score -=1;
			combo=0;
		}
	}
}
void check_f(const int i,int map[][4]){
	attron(COLOR_PAIR(4));
	mvprintw(19,8,"====");
	attroff(COLOR_PAIR(4));
	refresh();
	int sizeOfMap=size_map(map);
	if(i>LINES_OF_BOARD && i<sizeOfMap){
		if(map[i-LINES_OF_BOARD-2][1]){
			attron(COLOR_PAIR(3));
			mvprintw(19,8,"@@@@");
			attroff(COLOR_PAIR(3));
			combo++;
			score +=5;
		}else{
			score -=1;
			combo=0;
		}
	}
}
void check_k(const int i,int map[][4]){
	attron(COLOR_PAIR(4));
	mvprintw(19,13,"====");
	attroff(COLOR_PAIR(4));
	refresh();
	int sizeOfMap=size_map(map);
	if(i>LINES_OF_BOARD && i<sizeOfMap){
		if(map[i-LINES_OF_BOARD-2][2]){
			attron(COLOR_PAIR(3));
			mvprintw(19,13,"@@@@");
			attroff(COLOR_PAIR(4));
			combo++;
			score +=5;
		}else{
			score -=1;
			combo=0;
		}
	}
}
void check_l(const int i, int map[][4]){
	attron(COLOR_PAIR(4));
	mvprintw(19,18,"====");
	attroff(COLOR_PAIR(4));
	refresh();
	int sizeOfMap=size_map(map);
	if(i>LINES_OF_BOARD && i<sizeOfMap){
		if(map[i-LINES_OF_BOARD-2][3]){
			attron(COLOR_PAIR(3));
			mvprintw(19,18,"@@@@");
			attroff(COLOR_PAIR(3));
			combo++;
			score +=5;
		}else{
			score -=1;
			combo=0;
		}
	}
}
void game(int default_map[][4]){
	int buffer = 0;
	int i =0;
	score = 0;
	while(default_map[i][0] != 7){
		for(int j = i -buffer,k = 0; j<=i; j++,k++){
			for(int d = 0; d<4;d++){
				if(default_map[j][d]){
					if(d%2 ==0){
						attron(COLOR_PAIR(1));
					}else{
						attron(COLOR_PAIR(2));
					}
					mvprintw(2+14-k,3 +d*5,"#");
					mvprintw(2+14-k,4 +d*5,"#");
					mvprintw(2+14-k,5 +d*5,"#");
					mvprintw(2+14-k,6 +d*5,"#");
					refresh();
					if(d%2 ==0){
						attroff(COLOR_PAIR(1));
					}else{
						attroff(COLOR_PAIR(2));
					}
				}else{
					mvprintw(2+14-k,3 +d*5," ");
					mvprintw(2+14-k,4 +d*5," ");
					mvprintw(2+14-k,5 +d*5," ");
					mvprintw(2+14-k,6 +d*5," ");
				}
			}

		}
		move(0,8);
		printw("%d",score);
		if(buffer < LINES_OF_BOARD){
			buffer++;
		}else if(i-buffer >0){
			for(int d = 0; d<4;d++){
				if(default_map[i-buffer-1][d]){
					if(d%2 ==0){
						attron(COLOR_PAIR(1));
					}else{
						attron(COLOR_PAIR(2));
					}
					mvprintw(17,3+d*5,"#");
					mvprintw(17,4+d*5,"#");
					mvprintw(17,5+d*5,"#");
					mvprintw(17,6+d*5,"#");
					if(d%2 ==0){
						attroff(COLOR_PAIR(1));
					}else{
						attroff(COLOR_PAIR(2));
					}

				}else{
					mvprintw(17,3+d*5,"-");
					mvprintw(17,4+d*5,"-");
					mvprintw(17,5+d*5,"-");
					mvprintw(17,6+d*5,"-");
				}
			}
		}
		int time_delay = 150;
			int flag_d = 1;
			int flag_f = 1;
			int flag_k = 1;
			int flag_l = 1;
		while(time_delay >0){
			int input = getch();
			switch(input){
				case 'd':case'D':{
					if(flag_d){
						flag_d=0;
						check_d(i,default_map);
					}
					break;
				}
				case 'f':case 'F':{
					if(flag_f){
						flag_f=0;
						check_f(i,default_map);
					}
					break;
				}
				case 'k':case 'K':{
					if(flag_k){
						flag_k = 0;
						check_k(i,default_map);
					}
					break;
				}
				case 'l':case 'L':{
					if(flag_l){
						flag_l =0;
						check_l(i,default_map);
					}
					break;
				}
			}
			time_delay -=1;
			napms(1);
		}
		napms(150 - time_delay);
		mvprintw(19,0,"  | D  | F  | K  | L  | ");
		refresh();
		i++;
	}
	for(int d= 0; d<4;d++){
		mvprintw(17,3+d*5,"-");
		mvprintw(17,4+d*5,"-");
		mvprintw(17,5+d*5,"-");
		mvprintw(17,6+d*5,"-");
	}
	napms(2500);
	refresh();
}
void chose_map(int map[][4],char lvl[]){
	clear();
	refresh();
	int x=5;
	FILE *actual_map = fopen("map_list.ml","r");
	if(actual_map == NULL){
		finish();
	}
	char map_names[100][15];
	char ch = fgetc(actual_map);
	map_names[0][0] = ch;
	int count_map = 0, i = 1;
	while(ch !=EOF){
		ch = fgetc(actual_map);
		if(ch == ' '){
			map_names[count_map][i]  = '\0';
			count_map++;
			i = 0;
		}else{
			map_names[count_map][i] = ch;
			i++;
		}
	}
	fclose(actual_map);
	map_names[count_map+1][0] = '\0';
	for(int i = 0; i<count_map; i++){
		if(i > 7*(x/5) ){
			x+=5;
		}
		mvprintw(i+3,x,"[%d] %s", i+1, map_names[i]);
	}
	
	refresh();
	int input;
	while(1){
		input = getch();
		if(input >47 && input <59){
			break;
		}
		napms(100);
	}
	char map_file_name[18];
	i =0;
	clear();
	for(; map_names[input-49][i]; i++){
		map_file_name[i] = map_names[input-49][i];
	}
	map_file_name[i]='.';
	map_file_name[i+1]='h';
	map_file_name[i+2]='h';
	map_file_name[i+3]='\0';
	mvprintw(0,0,"Loading %s",map_file_name);
	refresh();
	FILE *map_file = fopen(map_file_name,"r");
	if(map_file == NULL){
		mvprintw(1,0,"Error opening file. Program will end in 4 sec");
		refresh();
		napms(4000);
		finish();
	}
	int j=0;
	i=0;
	while((ch = fgetc(map_file)) != EOF){
		if(ch == '\n') continue;
		map[i][j] = ch-48;

		j++;
		if(j == 4){
			j=0;
			i++;
		}
	}
	int n;
	for( n = 0; map_file_name[n] !='.';n++){
		lvl[n] = map_file_name[n];
	}
	lvl[n] ='\0';
	clear();
	refresh();
	fclose(map_file);
}
void start_game(){
		clear();
		int map[200][4];
		char lvl[15];
		chose_map(map,lvl);
		make_zone_of_game(lvl);
		game(map);
		end_menu(map,lvl);
}
void menu(){
	clear();
	mvprintw(5,3,"[S] Start game");
	mvprintw(6,3,"[Q] Quit");
	refresh();
	while(1){
		int input = getch();
		switch(input){
			case 's' :case 'S':{
				start_game();
				break;
			}
			case 'q':case 'Q':{
				finish();
			}
		}
	napms(500);
	}
}
void end_menu(int default_map[][4],char lvl[]){
	clear();
	mvprintw(5,3,"[R] Restar game");
	mvprintw(6,3,"[C] Choose other map");
	mvprintw(7,3,"[Q] Quit a game");
	refresh();
	while(1){
		int input = getch();
		switch(input){
			case 'r': case 'R':{
				make_zone_of_game(lvl);
				game(default_map);
				break;
			}
			case 'c': case'C':{
				start_game();
				break;
			}
			case 'q':case 'Q':{
				finish();
				break;
			}
		}
		napms(100);
	}
}
int main(){
	init();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_RED, COLOR_RED);


	//make_zone_of_game();
	refresh();
	menu();
	napms(5000);
	finish();
	return 0;
}

