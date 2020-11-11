#include "Enemy1.h"
#include "Player.h"
#include "SDL.h"

Entity *enemy1_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);
	self->think = enemy1_think;
	self->collide = enemy1_collision;
	self->velocity = 0.08;
	//STATS
	self->velocity = 1;
	self->position.x += 110;
	self->position.y += 45;

	//Collider
	self->collision_offset = vector3d(5, 5, 5);
	slog("Enemy1 Ent Created");
	return self;
}

void enemy1_think(Entity *self){
	enemy1_move(self);
}

void enemy1_move(Entity *self){
	Vector3D player = player_active()->position;
	Vector3D pos = self->position;
	
	if (pos.x < player.x){
		self->position.x += 0.08;
	}
	if (pos.x > player.x){
		self->position.x -= 0.08;
	}
	if (pos.y < player.y){
		self->position.y += 0.08;
	}
	if (pos.y > player.y){
		self->position.y -= 0.08;
	}
	gfc_matrix_make_translation(self->modelMatrix, self->position);
}

void enemy1_collision(Entity *self, Entity *ent2){
	enemy1_attack(self, ent2);
	//entity_free(self);
}

void enemy1_attack(Entity *self, Entity *ent2){
	if (!ent2->invincible){
		ent2->health -= 10;
		ent2->position.z += 3;
	}
}