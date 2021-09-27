#include <superkarel.h>
#define SPEED 1
void turn_right(); void reverse();	bool is_perk(); void take_row();
int main(){
	turn_on("task_3.kw");
	set_step_delay(SPEED);
	do{
		take_row();
		reverse();
		while(front_is_clear()){
			if(beepers_in_bag()){
				if(is_perk()){
					put_beeper();
				}
			}
			step();
		}
		turn_left();
		if(front_is_blocked()){
			break;
		}
		step();
		turn_left();
	}while(left_is_clear());

	turn_left();
	while(front_is_clear()){
		step();
	}
	turn_left();
while(left_is_clear()){
	while(front_is_clear()){
		step();
	}
	if(beepers_present()){
		turn_left();
		while(front_is_clear()){
			step();
		}
		reverse();
		break;
	}else{
		reverse();
		while(front_is_clear()){
			step();
		}
		turn_right();
		step();
		turn_right();
	}
}
	turn_off();
	return 0;
}
void take_row(){
	while(front_is_clear()){
		if(beepers_present()){
			pick_beeper();
		}
		step();
	}
	if(beepers_present()){
		pick_beeper();
	}
}
bool is_perk(){
	if(right_is_blocked()){
		return true;
	}else{
		turn_right();
		step();
		if(beepers_present()){
			reverse();
			step();
			turn_right();
			return true;
		}else{
			reverse();
			step();
			turn_right();
			return false;
		}
	}
}
void reverse(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(SPEED);
}
void turn_right(){
	set_step_delay(0);
	turn_left();
    turn_left();
    set_step_delay(SPEED);
    turn_left();
}
