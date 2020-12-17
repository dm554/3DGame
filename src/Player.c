#include "Player.h"
#include "SDL.h"
#include "combat.h"
static Entity *THE_PLAYER;
static Entity *target;

Entity *player_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);
	self->think = player_think;
	self->collide = player_collision;

	//PLAYER STATS
	self->velocity = 1;
	self->state = 1;
	self->gravity = 0.3;
	self->stamina = 100;
	self->speedPad = 0;
	self->health = 50;
	self->sprintFactor = 1;
	self->starting_height = self->position.z;

	//Collider
	self->collision_offset = vector3d(5, 5, 5);
	THE_PLAYER = self;
	slog("Player Ent Created");
	return self;
}

void player_think(Entity *self){
	player_input(self);
	player_gravity(self);
	//slog("Health: %f", self->health);
	//slog("X: %f, Y: %f", self->position.x, self->position.y);
}

void player_input(Entity *self){
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	
	//Entity Destruction
	if (buttons[SDL_SCANCODE_X]){
		entity_free(self);
	}
	player_stat_reset(self);
	player_attack_command(self, buttons);
	player_ability(self, buttons);
	player_increment(self);
	player_move(self, buttons);

	//NOTE: Y AND Z AXIS ARE FLIPPED?
}

void player_move(Entity *self, Uint8 *buttons){
	
	//MULTI INPUT DIRECTIONS
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_UP]){
		self->position.x -= (0.1 * self->velocity);
		self->position.y -= (0.1 * self->velocity);
		self->rotation.z = -0.75;
		self->angle = 2;
	}
	else if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x -= (0.1 * self->velocity);
		self->position.y += (0.1 * self->velocity);
		self->rotation.z = -2.25;
		self->angle = 4;
	}
	else if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_UP]){
		self->position.x += (0.1 * self->velocity);
		self->position.y -= (0.1 * self->velocity);
		self->rotation.z = 0.75;
		self->angle = 8;
	}
	else if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x += (0.1 * self->velocity);
		self->position.y += (0.1 * self->velocity);
		self->rotation.z = 2.25;
		self->angle = 6;
	}

	//SINGLE INPUT DIRECTIONS
	else if (buttons[SDL_SCANCODE_RIGHT]){
		self->position.x -= (0.1 * self->velocity);
		self->rotation.z = -1.5;
		self->angle = 3;
	}
	else if (buttons[SDL_SCANCODE_LEFT]){
		self->position.x += (0.1 * self->velocity);
		self->rotation.z = 1.5;
		self->angle = 7;
	}
	else if (buttons[SDL_SCANCODE_UP]){
		self->position.y -= (0.1 * self->velocity);
		self->rotation.z = 0;
		self->angle = 1;
	}
	else if (buttons[SDL_SCANCODE_DOWN]){
		self->position.y += (0.1 * self->velocity);
		self->rotation.z = 3.0;
		self->angle = 5;
	}
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.z, vector3d(0, 0, 1));
	//gfc_matrix_slog(self->modelMatrix);
}

void player_ability(Entity *self, Uint8 *buttons){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type){
			/* Look for a keypress */
		case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch (event.key.keysym.sym){
			case SDLK_SPACE:
				if (self->position.z < 4){ player_jump(self); }
				break;
			case SDLK_LCTRL:
				player_dodge(self);
				break;
			case SDLK_q:
				combat_engage(self, 1);
				break;
			case SDLK_e:
				combat_engage(self, 2);
				break;
			case SDLK_r:
				combat_engage(self, 3);
				break;
			case SDLK_1:
				player_attack_rise(self, 20);
				break;
			default:
				break;
			}
		}
	}
	if (buttons[SDL_SCANCODE_LSHIFT]){
		player_sprint(self);
	}
	if (self->speedPad > 0){
		if (buttons[SDL_SCANCODE_SPACE]){
			self->position.z += 0.5;
			self->speedPad--;
			slog("jetpack");
		}
	}
}

void player_sprint(Entity *self){
	if (self->stamina > 0){
		self->velocity += self->sprintFactor;
		self->stamina -= 0.1;
	}
	slog("Sprint");
}

void player_jump(Entity *self){
	self->state = 3;
	self->jumptime = 15;
	slog("Jump");
}

void player_dodge(Entity *self){
	if (self->stamina > 30){
		self->stamina -= 30;
		self->dashtime = 5;
		self->state = 4;
		slog("dodge");
	}
}

Entity *player_active(){
	if (THE_PLAYER != NULL){
		return THE_PLAYER;
	}
}

void player_collision(Entity *self, Entity *ent2){
	
	//slog("Collision Detected");
	if (self->state == 3){
		player_attack(self, ent2);
	}
	target = ent2;
	
}

void player_attack(Entity *self, Entity *ent2){
	//ent2->position.x += 1;
	//gfc_matrix_make_translation(ent2->modelMatrix, ent2->position);
	//self->state = 1;
}

void player_attack_command(Entity *self, Uint8 *buttons){
	if (buttons[SDL_SCANCODE_W]){
		self->state = 3;
	}

}

void player_gravity(Entity *self){
	if (self->position.z > self->starting_height){
		self->position.z -= self->gravity;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.z, vector3d(0, 0, 1));
	}
}

void player_stat_reset(Entity *self){
	self->velocity = 1;
}

void player_increment(Entity *self){
	if (self->state = 3 && self->jumptime > 0){
		self->jumptime--;
		self->position.z += 0.7;
	}
	if (self->state = 4 && self->dashtime > 0){
		self->dashtime--;
		self->velocity = 20;
	}
	else{
		self->stamina += 0.1;
	}
}

Entity *player_target(){
	return target;
}

void player_attack_rise(Entity *self, int range){
	/*self->collision_offset.x += range;
	self->collision_offset.y += range;
	player_target()->position.z += 5;
	self->collision_offset.x -= range;
	self->collision_offset.y -= range;
	slog("attack rise");
	*/

	player_aoe_checker(self, 10, 0, 0, 10);
}

void player_attack_stun(Entity *self, int range);
void player_attack_knockback(Entity *self, int range);

void player_ability_heal(Entity *self){ 
	if (self->meter > 50){
		self->health += (self->meter = -50);
	} 
	else if (self->meter == 50){
		self->health += 50;
	}
}

void player_ability_chi(Entity *self){
	
	if (self->meter >= 50){
		if (self->chi < 2){
			self->chi++;
			self->meter -= 50;
		}
		else if (self->chi == 2){
			self->chi = 0;
			//chi blast
		}
	}

}

void player_aoe_checker(Entity *self, float range, float knockback, float hitstun, float knockup){
	EntityManager entity_manager;
	int i;
	if (!self)return;
	
	entity_manager = get_entity_manager();

	for (i = 0; i < entity_manager.entity_count; i++)
	{
		if (!entity_manager.entity_list[i]._inuse)continue;
		if (&entity_manager.entity_list[i] == self)continue;
		
		if (player_aoe_range_check(self, &entity_manager.entity_list[i], range)){
			entity_manager.entity_list[i].position.z += knockup;
		}
	}
}

int player_aoe_range_check(Entity *self, Entity *enemy, float maxRange){
	float distancex = abs(self->position.x - enemy->position.x);
	float distancey = abs(self->position.y - enemy->position.y);

	if (distancex <= maxRange && distancey <= maxRange){
		return 1;
	}
	else{
		return 0;
	}
}


