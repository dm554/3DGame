#include "Player.h"

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
	
	//Entity Destruction
	if (buttons[SDL_SCANCODE_X]){
		entity_free(self);
	}

	
	//Movement Input

	//SINGLE INPUT DIRECTIONS
	if (buttons[SDL_SCANCODE_RIGHT]){
		self->position.x -= (0.1 * self->velocity);
	}
	else if (buttons[SDL_SCANCODE_LEFT]){
		self->position.x += (0.1 * self->velocity);
	}
	else if (buttons[SDL_SCANCODE_UP]){
		self->position.y -= (0.1 * self->velocity);
	}
	else if (buttons[SDL_SCANCODE_DOWN]){
		self->position.y += (0.1 * self->velocity);
	}

	//MULTI INPUT DIRECTIONS
	else if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_UP]){

	}
	else if(buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){

	}
	else if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_UP]){

	}
	else if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){

	}

	gfc_matrix_make_translation(self->modelMatrix, self->position);


	//NOTE: Y AND Z AXIS ARE FLIPPED?
}