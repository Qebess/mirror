
#include <stdio.h>
#include "hof.h"
#include "k.h"
#include "ui.h"


int main(){
	struct game game = {
	    .board = {
	    {'A', ' ', ' ', ' '},
	    {' ', ' ', ' ', ' '},
	    {' ', ' ', ' ', 'A'},
	    {'B', ' ', ' ', ' '}
	    },
	    .score = 0
	};
    printf("is won: %d\n", is_game_won(game));
	add_random_tile(&game);
	add_random_tile(&game);

	printf("is move possible: %d\n", is_move_possible(game));
    bool result = update(&game, 0, 1);
	printf("%d\n",result);
	struct player list[10];
	int size = load(list);
	struct player player = {
	    .name = "John",
	        .score = 100
	        };

	result = add_player(list, &size, player);
	save(list,size);
	render(game);
		
}

