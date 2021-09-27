#include <superkarel.h>
#define SPEED 100

void reverse(); void turn_right(); void check();

int main(){
	turn_on("task_7.kw");
	set_step_delay(SPEED);
	while(front_is_clear()){
		if(left_is_clear()){
			put_beeper();
		}
		step();
	}
	if(left_is_clear()){
		put_beeper();
	}
	reverse();
	while(front_is_clear()){
		step();
	}
	reverse();
	while(no_beepers_present()){
		step();
	}
	while(front_is_clear()){
		check();
	}
	if(beepers_present()){
		check();
	}
	if(beepers_present()){
		pick_beeper();
	}
	turn_off();
	return 0;
}
void reverse(){ set_step_delay(0); turn_left(); set_step_delay(SPEED); turn_left();}
void turn_right(){ set_step_delay(0); turn_left(); turn_left(); set_step_delay(SPEED); turn_left();}
void check(){
	turn_left();
	step();
	while(no_beepers_present()){
		if(right_is_clear()){
			turn_right();
		}else if(left_is_clear() && front_is_blocked()){
			turn_left();
		}else if(front_is_blocked()){
			reverse();
		}
		step();
	}
	turn_right();
	do{
		if(front_is_blocked()){
			reverse();
			while(no_beepers_present()){
				step();
			}
			break;
		}
		step();
	} while(no_beepers_present());
	if(facing_west()){
		pick_beeper();
		turn_right();
		step();
		put_beeper();
		reverse();
		step();
		turn_left();
		while(no_beepers_present()){
			if(front_is_blocked()){
				break;
			}
			step();
		}
		pick_beeper();
		turn_left();
		step();
		put_beeper();
		reverse();
		step();
		turn_left();
	}else{
		pick_beeper();
	}
	while(no_beepers_present()){
		if(front_is_blocked()){
			break;
		}
		step();
	}
}


