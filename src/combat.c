#include "combat.h"
#include "Player.h"

static int input_1;
static int input_2;
static int input_3;
static int input_count;

void combat_engage(Entity *player, int player_input){
	combo_router(player, player_input);
}

void combo_router(Entity *player, int player_input){
	
	input_counter(player_input);
	slog("combat hit run");
	switch (input_count){
		case 1:
			if (input_1 = 1){
				//Light Attack 1
			}
			else if (input_1 = 2){
				//Medium Attack 1
			}
			else if (input_1 = 3){
				//Heavy Attack 
			}
			else{
				input_clear();
			}
			break;
		case 2:
			if ((input_1 = 1) && (input_2 = 1)){
				//Light Combo Attack 2
			}
			else if ((input_1 = 2) && (input_2 = 2)){
				//Medium Combo Attack 2
			}
			else if ((input_1 = 3) && (input_2 = 3)){
				//Heavy Combo Attack 2
			}
			else if ((input_1 = 1) && (input_2 = 2)){
				//Magic Series Attack 2
			}
			else if ((input_1 = 1) && (input_2 = 3)){
				//One, two punch
			}
			else{
				input_clear();
			}
			break;
		case 3:
			if ((input_2 = 1) && (input_3 = 1)){
				//Light Combo Attack 3
			}
			else if ((input_2 = 2) && (input_2 = 2)){
				//Medium Combo Attack 3
			}
			else if ((input_2 = 3) && (input_3 = 3)){
				//Heavy Combo Attack 3
			}
			else if ((input_2 = 2) && (input_3 = 3)){
				//Magic Series Attack 3
			}
			input_clear();
			break;
	}
}
	

void input_clear(){
	input_1 = 0;
	input_2 = 0;
	input_3 = 0;
	input_count = 0;
}

void combat_hit(Entity *player, float hitstun, float knockback){
	
	Entity *target = player_target();
	if (target != NULL){
		target->hitstun += hitstun;
		target->position.y += knockback;
		target->position.z += knockback;
	}

}

void input_counter(int input){
	input_count++;
	switch (input_count)
	{
	case 1:
		input_1 = input;
		break;
	case 2:
		input_2 = input;
		break;
	case 3:
		input_3 = input;
		break;
	}

}