#include "Player.h"

static Entity *THE_PLAYER;

Entity *player_new(){

	Entity *self;
	self = entity_new();
	
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);
	self->think = player_think;

	//PLAYER STATS
	self->velocity = 1;

	slog("Player Ent Created");
	return self;
}

void player_think(Entity *self){
	player_input(self);
}

void player_input(Entity *self){
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	float speed = 0.1 * self->velocity;
	//Entity Destruction
	if (buttons[SDL_SCANCODE_X]){
		entity_free(self);
	}
	//Movement Input

	//MULTI INPUT DIRECTIONS
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_UP]){
		self->position.x -= (0.1 * self->velocity);
		self->position.y -= (0.1 * self->velocity);
		self->rotation.z = -0.75;
	}
	else if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x -= (0.1 * self->velocity);
		self->position.y += (0.1 * self->velocity);
		self->rotation.z = -2.25;
	}
	else if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_UP]){
		self->position.x += (0.1 * self->velocity);
		self->position.y -= (0.1 * self->velocity);
		self->rotation.z = 0.75;
	}
	else if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x += (0.1 * self->velocity);
		self->position.y += (0.1 * self->velocity);
		self->rotation.z = 2.25;
	}

	//SINGLE INPUT DIRECTIONS
	else if (buttons[SDL_SCANCODE_RIGHT]){
		self->position.x -= (0.1 * self->velocity);
		self->rotation.z = -1.5;
		slog("Rotating");
	}
	else if (buttons[SDL_SCANCODE_LEFT]){
		self->position.x += (0.1 * self->velocity);
		self->rotation.z = 1.5;
	}
	else if (buttons[SDL_SCANCODE_UP]){
		self->position.y -= (0.1 * self->velocity);
		self->rotation.z = 0;
	}
	else if (buttons[SDL_SCANCODE_DOWN]){
		self->position.y += (0.1 * self->velocity);
		self->rotation.z = 3.0;
	}



	gfc_matrix_make_translation(self->modelMatrix, self->position);
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.z, vector3d(0, 0, 1));


	//NOTE: Y AND Z AXIS ARE FLIPPED?
}

Entity *player_active(){
	if (THE_PLAYER != NULL){
		//return THE_PLAYER;
	}
}