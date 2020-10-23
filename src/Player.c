#include "Player.h"

Entity *player_new(){

	Entity *self;
	self = entity_new();
	
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);

	slog("Player Ent Created");
	return self;
}