#include <superkarel.h>
#define SPEED 150
void step_untill_numb(); void turn_to_WNES();
int main(){
	turn_on("task_6.kw");
	set_step_delay(SPEED);
	while(1){
		step_untill_numb();
		turn_to_WNES();
	}
	turn_off();
	return 0;
}

void step_untill_numb(){
	while(no_beepers_present()){
		step();
	}
}
void turn_to_WNES(){
	while(not_facing_east()){
		turn_left();
	}
	if(beepers_present()){
		pick_beeper();
		turn_left();
	}
	if(beepers_present()){ 
        pick_beeper();
        turn_left();
    }
    if(beepers_present()){ 
        pick_beeper();
        turn_left();
    }
    if(beepers_present()){ 
        pick_beeper();
        turn_left();
    }
    if(beepers_present()){
    	pick_beeper();
		turn_off();
    }
}
