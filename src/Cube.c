#include "Cube.h"
#include "Player.h"

Entity *cube_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("cube");
	gfc_matrix_identity(self->modelMatrix);
	self->think = cube_think;
	self->collide = cube_collide;
	self->position.x = 10;
	self->position.z = -5;
	self->rotation.z += 0.01;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	self->velocity = 1;

	//Collider
	self->collision_offset = vector3d(1, 1, 5);
	slog("Cube Ent Created");
	return self;
}

void cube_think(Entity *self){
	
	gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, self->rotation.z, vector3d(0, 0, 1));
}

void cube_collide(Entity *self, Entity *ent2){
	slog("collision detected");
	cube_powerups(ent2);
	entity_free(self);
}

void cube_powerups(Entity *ent2){
	//int powerup = rand() % 4;
	int powerup = 1;
	switch (powerup){
		case 0:
			cube_speed(1500, 5);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
	}
}

void cube_speed(int timer, float speed){
	for (int i = 0; i < timer; i++){
		Entity *player = player_active();
		player->velocity = speed;
		if (i == (timer - 1)){
			player->velocity = 1;
		}
	}
}