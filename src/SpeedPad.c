#include "SpeedPad.h"

Entity *speedpad_new(){
	
	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("cube");
	gfc_matrix_identity(self->modelMatrix);
	self->position.x -= 10;
	self->rotation.x = 1.6;
	self->collision_offset = vector3d(1, 1, 10);
	self->think = speedpad_think;
	self->collide = speedpad_collide;
	self->speedPad = 1;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.x, vector3d(1, 0, 0));

	return self;
}

void speedpad_think(Entity *self){}

void speedpad_collide(Entity *self, Entity *ent2){
	slog("speed");
}