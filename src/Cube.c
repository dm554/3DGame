#include "Cube.h"
#include "Player.h"

Entity *cube_new(int type, float x){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("cube");
	gfc_matrix_identity(self->modelMatrix);
	self->think = cube_think;
	self->collide = cube_collide;
	self->position.x = x;
	self->position.y += -90;
	self->position.z = -5;
	self->rotation.z += 0.01;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	self->velocity = 1;
	self->state = type;
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
	cube_powerups(ent2, self->state);
	entity_free(self);
}

void cube_powerups(Entity *ent2, int type){
	//int powerup = rand() % 4;
	int powerup = type;
	switch (powerup){
		case 0:
			cube_speed(3000, 5);
			break;
		case 1:
			cube_low_gravity(3000, 0.07);
			break;
		case 2:
			cube_health(20);
			break;
		case 3:
			cube_stamina(40);
			break;
		case 4:
			cube_invincible(1500);
			break;
	}
}

void cube_speed(int timer, float speed){
	for (int i = 0; i < timer; i++){
		Entity *player = player_active();
		player->sprintFactor = speed;
		player->speedUp = 1;
		slog("speedup");
		if (i == (timer - 1)){
			//player->sprintFactor = 1;
			player->speedUp = 0;
			slog("speedUp end");
		}
	}
}

void cube_low_gravity(int timer, float new_gravity){
	for (int i = 0; i < timer; i++){
		Entity *player = player_active();
		player->gravity = new_gravity;
		if (i == (timer - 1)){
			player->gravity = 0.03;
		}
	}
}

void cube_health(int amount){
	for (int i = 0; i < amount; i++){
		player_active()->health += 1;
	}
}

void cube_stamina(int amount){
	for (int i = 0; i < amount; i++){
		player_active()->stamina += 1;
	}
}

void cube_invincible(int timer){
	for (int i = 0; i < timer; i++){
		Entity *player = player_active();
		player->health = 100;
		player->invincible = 1;
	}
	
}