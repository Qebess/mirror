#include <stdio.h>
#include <stdlib.h>

#include "k.h"

bool is_game_won(const struct game game);
void add_random_tile(struct game *game);
bool is_move_possible(const struct game game);
bool update(struct game *game, int dy, int dx);




void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
	for(int i = 0; i<SIZE; i++){
		for(int j = 0; j<SIZE; j++){
			if(game.board[i][j]=='K'){
				return 1;
			}
		}
	}
	return 0;
}
bool is_move_possible(const struct game game){
	for(int i = 0; i<SIZE; i++){
		for(int j = 0; j<SIZE; j++){
			if(game.board[i][j] == ' '){
				return 1;
			}
		}
	}
	for(int i = 0; i<SIZE-1; i++){
		for(int j = 0; j<SIZE; j++){
			if(game.board[i][j] == game.board[i+1][j]){
				return 1;
			}
		}
	}
	for(int i = 0; i<SIZE; i++){
		for(int j = 0; j<SIZE-1; j++){
			if(game.board[i][j] == game.board[i][j+1]){
				return 1;
			}
		}
	}
	return 0;
}
//ABCDEFGHIJK
bool update(struct game *game, int dy, int dx){
/////force start 
	bool force(char row[SIZE], struct game *game){
		const char chars[] ="ABCDEFGHIJK";
		bool changed = 0;
		bool clay[SIZE];
		for(int i = 0; i<SIZE;i++){clay[i]=1;}
		for(int i = SIZE-1; i >-1 ;i--){
			if(row[i] != ' '){
				int j =i+1;
				for(; j<SIZE;j++){
					if(row[j] != ' '){
						if(row[i] == row[j] && clay[j] == 1){
							int pos_l =0;
							for(;chars[pos_l]!=row[i];pos_l++);
							row[j] = chars[pos_l+1];
							int pow =2;
							for(;pos_l >0;pow*=2,pos_l--);
							game->score +=pow*2;
							row[i] = ' ';
							clay[j] = 0;
							changed = 1;
							break;
						}else{
							if(j-1 != i){
								row[j-1] = row[i];
								row[i] = ' ';
								changed =1;
							}
							break;
						}
					}
					if(j ==SIZE-1 && row[j] == ' '){
						row[j] = row[i];
						row[i] = ' ';
						changed =1;
						continue;
					}
				}
			}
		}
		return changed;
	}
////force end
	bool changed = 0;
	if(!((dx==1 && dy ==0) || (dx==-1 && dy ==0) || (dx==0 && dy ==1) || (dx==0 && dy ==-1))){
		return false;
	}
	char row[SIZE];
	if(dx == 1){
		for(int i = 0; i<SIZE;i++){
			for(int k = SIZE -1, j = SIZE-1; j>-1; j--,k--){
				row[k] = game->board[i][j];
			}
			if(force(row, game)){changed =1;}
			for(int k = SIZE -1, j = SIZE-1; j>-1; j--,k--){
				game->board[i][j] = row[k];
			}
		}
		return changed;
	}else if(dx == -1){
		for(int i= 0; i <SIZE;i++){
			for(int k = SIZE -1,  j = 0; j<SIZE; j++,k--){
				row[k] = game->board[i][j];
			}
			if(force(row, game)){changed =1;}
			for(int k =SIZE -1,  j = 0; j<SIZE; j++,k--){
				game->board[i][j] = row[k];
			}
		}
		return changed;
	}else if(dy ==-1){
		for(int j= 0; j <SIZE;j++){
			for(int k = 0,  i = SIZE- 1; i>-1; i--,k++){
				row[k] = game->board[i][j];
			}
			if(force(row, game)){changed =1;}
			for(int k =0,  i = SIZE -1; i>-1; i--,k++){
				game->board[i][j] = row[k];
			}
		}
			return changed;
	}else if(dy ==1){
		for(int j= 0; j <SIZE;j++){
			for(int k = 0,  i = 0; i<SIZE; i++,k++){
				row[k] = game->board[i][j];

			}
			if(force(row, game)){changed =1;}
		
			for(int k =0,  i = 0; i<SIZE; i++,k++){
				game->board[i][j] = row[k];
			}
		}
		return changed;
	}
	return changed;
}


//int main(){
//struct game game = {
//.score=8832,
//.board={
//	{'J', 'H', ' ', ' '},
//		{' ', ' ', ' ', 'I'},
//			{'F', 'J', ' ', ' '},
//				{' ', ' ', 'B', 'B'}
//				}};
//	for(int i = 0; i<4; i++){
//		for(int j = 0; j<4; j++){
//			printf("%c ",game.board[i][j]);
//		}
//		printf("\n");
//	}
//	printf("=================\n");
//
//	bool ok = update(&game,-1,0);
//	for(int i = 0; i<4; i++){
//		for(int j = 0; j<4; j++){
//			printf("%c ",game.board[i][j]);
//		}
//		printf("\n");
//	}
//	printf("ok : %d\n",ok);
//	return 0;
//}
