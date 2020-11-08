#include "Player.h"

static Entity *THE_PLAYER;

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

	//Collider
	self->collision_offset = vector3d(5, 5, 5);
	THE_PLAYER = self;
	slog("Player Ent Created");
	return self;
}

void player_think(Entity *self){
	player_input(self);
}

void player_input(Entity *self){
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	
	//Entity Destruction
	if (buttons[SDL_SCANCODE_X]){
		entity_free(self);
	}
	
	player_attack_command(self, buttons);
	player_ability(self, buttons);
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
	if (buttons[SDL_SCANCODE_SPACE]){
		player_jump(self);
	}
	else if (buttons[SDL_SCANCODE_LSHIFT]){
		player_sprint(self);
	}
}

void player_sprint(Entity *self){
	slog("Sprint");
}

void player_jump(Entity *self){
	slog("Jump");
}

void player_dodge(Entity *self){

}

Entity *player_active(){
	if (THE_PLAYER != NULL){
		return THE_PLAYER;
	}
}

void player_collision(Entity *self, Entity *ent2){
	
	slog("Collision Detected");
	if (self->state == 3){
		player_attack(self, ent2);
	}
	
}

void player_attack(Entity *self, Entity *ent2){
	ent2->position.x += 1;
	gfc_matrix_make_translation(ent2->modelMatrix, ent2->position);
	//self->state = 1;
}

void player_attack_command(Entity *self, Uint8 *buttons){
	if (buttons[SDL_SCANCODE_W]){
		self->state = 3;
	}

}