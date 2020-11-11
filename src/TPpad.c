#include "TPpad.h"

Entity *telpad_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("cube");
	gfc_matrix_identity(self->modelMatrix);
	self->position.x -= 15;
	self->position.y += 20;
	self->rotation.x = 1.6;
	self->collision_offset = vector3d(1, 1, 10);
	self->think = telpad_think;
	self->collide = telpad_collide;
	self->speedPad = 1;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.x, vector3d(1, 0, 0));

	return self;
}

void telpad_think(Entity *self){}

void telpad_collide(Entity *self, Entity *ent2){
	Vector3D new_position = vector3d(self->position.x * -1, self->position.y * -1, self->position.z * -1);
	ent2->position = new_position;
}