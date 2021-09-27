//version 0.0.2v
#include <superkarel.h>
#define SPEED 100
void recover();
void turn_right();
void reverse();
//void go_left();
bool column_is_broken();

int main(){
	turn_on("task_4.kw");
	set_step_delay(SPEED);
	do{
		turn_left();
		recover();
		turn_left();
		if(front_is_blocked()){
			break;
		}
		step();
	}while(front_is_clear());

	turn_left();
	recover();
	turn_left();

	turn_off();
	return 0;
}
void recover(){
	if(column_is_broken()){
		while(front_is_clear()){
			if(no_beepers_present()){
				put_beeper();
			}
			step();
			if(no_beepers_present()){
				put_beeper();
			}
		}
	}else{
		while(front_is_clear()){
			step();
		}
	}

}
bool column_is_broken(){
	while(front_is_clear()){
		if(beepers_present()){
			while(front_is_clear()){
				step();
			}
			reverse();
			return true;
		}else{
			step();
		}
	}
	if(beepers_present()){
		reverse();
		return true;
	}
	reverse();
	return false;
}
void turn_right(){ set_step_delay(0); turn_left(); turn_left(); set_step_delay(SPEED); turn_left();}
void reverse(){ set_step_delay(0); turn_left(); set_step_delay(SPEED); turn_left();}
