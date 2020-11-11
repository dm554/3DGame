#include "Floor.h"

Entity *floor_new(){
	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("bigfloor");
	gfc_matrix_identity(self->modelMatrix);
	self->rotation.x = 1.6;
	self->think = floor_think;
	self->collide = floor_collide;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.x, vector3d(1, 0, 0));
}

void floor_think(Entity *self){}

void floor_collide(Entity *self, Entity *ent2){}