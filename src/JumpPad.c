#include "JumpPad.h"

Entity *jumppad_new(){
	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("cube");
	gfc_matrix_identity(self->modelMatrix);
	self->position.x += -140;
	self->position.y += -80;
	self->rotation.x = 1.6;
	self->collision_offset = vector3d(1,1,1);
	self->think = jumppad_think;
	self->collide = jumppad_collide;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.x, vector3d(1, 0, 0));

	return self;
}

void jumppad_think(Entity *self){}

void jumppad_collide(Entity *self, Entity *ent2){
	slog("jumppad");
	ent2->position.z += 70;
}