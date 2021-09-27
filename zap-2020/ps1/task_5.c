#include <superkarel.h>
#define SPEED 1

void make_ramka(); void make4_ramka(); void turn_right(); void reverse(); void find_mid();
// test for arena
int main(){
	turn_on("task_5.kw");
	set_step_delay(SPEED);
    while(!facing_west()){
        turn_left();
    }
    while(front_is_clear()){
        step();
    }
    turn_left();
    while(front_is_clear()){
        step();
    }
    turn_left();


	make4_ramka();
	find_mid();
	turn_right();
	find_mid();
	turn_left();
	if(front_is_clear())
	step();
	turn_left();
	if(front_is_clear())
	step();


	turn_off();
	return 0;
}
void make_ramka(){
	while(front_is_clear()){
		if(no_beepers_present()){
			put_beeper();
		}
		step();
	}
	turn_left();
}
void make4_ramka(){
	make_ramka();
	make_ramka();
	make_ramka();
	make_ramka();
}

void find_mid(){
	if(front_is_blocked()){
		reverse();
	}else{
		step();
		if(front_is_clear()){
			step();
		}
		find_mid();
	}
	if(front_is_clear()){
		step();
	}
}

void turn_right(){ set_step_delay(0); turn_left(); turn_left(); set_step_delay(SPEED); turn_left();}
void reverse(){ set_step_delay(0); turn_left(); set_step_delay(SPEED); turn_left();}
