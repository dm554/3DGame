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
	switch (input_count){
		case 1:
			if (input_1 = 1){
				//Light Attack 1
				combat_hit(player, 1, 100,5);
			}
			else if (input_1 = 2){
				//Medium Attack 1
				combat_hit(player, 2, 200, 7);
			}
			else if (input_1 = 3){
				//Heavy Attack 
				combat_hit(player, 2, 300, 10);
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

void combat_hit(Entity *player, float hitstun, float knockback, int ex){

	//sets target variable 
	Entity *target = player_target();
	
	//check to see if there is a target
	if (target != NULL){

		//applies hitstun 
		target->hitstun += hitstun;
		player->meter += ex;
		//applies knockback
		switch (player->angle){
		case 1:
			target->position.y -= knockback;
			break;
		case 2:
			target->position.y -= knockback;
			target->position.x -= knockback;
			break;
		case 3:
			target->position.x -= knockback;
			break;
		case 4:
			target->position.y += knockback;
			target->position.x -= knockback;
			break;
		case 5:
			target->position.y += knockback;
			break;
		case 6:
			target->position.y += knockback;
			target->position.x += knockback;
			break;
		case 7:
			target->position.x += knockback;
			break;
		case 8:
			target->position.y -= knockback;
			target->position.x += knockback;
			break;
		}
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