#include "Player.h"

Entity *player_new(){

	Entity *self;
	self = entity_new();
	
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);
	self->think = player_think;
	slog("Player Ent Created");
	return self;
}

void player_think(Entity *self){
	player_input(self);
}

void player_input(Entity *self){
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	if (buttons[SDL_SCANCODE_X]){
		entity_free(self);
	}
}