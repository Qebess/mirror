#include <superkarel.h>


void reverse();
void go_inside();
bool go_outside();
void turn_right();

//test for arena
int main(){
	turn_on("task_2.kw");
	set_step_delay(100);
	go_inside();
	reverse();
	pick_beeper();
	if(go_outside()){
		turn_off();
		return 0;
	}


}
void go_inside(){
	while(!beepers_present()){
		if(front_is_blocked()){
			turn_left();
		}
		step();
	}
}
bool go_outside(){
	while(1){
		if(front_is_blocked()){
			turn_right();
			if(front_is_blocked()){
				return true;
			}
		}
		step();
	}

}


void turn_right(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(100);
	turn_left();
}
void reverse(){
	set_step_delay(0);
	turn_left();
	set_step_delay(100);
	turn_left();

}
