#include <superkarel.h>
//why i hate my code?
void jump_over();
void turn_right();
bool R_is_clear();
bool L_is_clear();
void jump_over_reverse();
void reverse();

int main(){
	turn_on("task_1.kw");

	set_step_delay(50);
	put_beeper();
	do{
		if(front_is_clear()){
			step();
		}else{
			jump_over();
		}
	}while(!beepers_present());
	pick_beeper();
	reverse();
	while(!beepers_present()){
		if(front_is_clear()){
			step();
		}else{
			jump_over_reverse();
		}
	}
	pick_beeper();
	turn_off();
	return 0;

}

void turn_right(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(500);
	turn_left();
}

bool L_is_clear(){
        turn_left();
        if(front_is_clear()){
                return true;
        }else{
                turn_right();
                return false;
        }
}

bool R_is_clear(){
        turn_right();
        if(front_is_clear()){
                return true;
        }else{
                turn_left();
                return false;
        }
}

void jump_over(){
	turn_left();
	step();
	while(!R_is_clear()){
		step();
	}
	step();
	while(!R_is_clear()){
		step();
	}
	while(front_is_clear()){
		step();
	}
	turn_left();
}

void jump_over_reverse(){
	turn_right();
	step();
	while(!L_is_clear()){
		step();
	}
	step();
	while(!L_is_clear()){
		step();
	}
	while(front_is_clear()){
		step();
	}
	turn_right();
}

void reverse(){
	turn_left();
	turn_left();
}


