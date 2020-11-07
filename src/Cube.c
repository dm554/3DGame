#include "Cube.h"

Entity *cube_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("cube");
	gfc_matrix_identity(self->modelMatrix);
	self->think = cube_think;

	//PLAYER STATS
	self->velocity = 1;

	//Collider
	self->collision_offset = vector3d(1, 1, 1);
	slog("Cube Ent Created");
	return self;
}

void cube_think(Entity *self){

}