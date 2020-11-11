#include "Enemy3.h"
#include "Player.h"
#include "SDL.h"

static Vector3D target_position;
Entity *enemy3_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);
	self->think = enemy3_think;
	self->collide = enemy3_collision;
	self->velocity = 0.08;
	//STATS
	self->velocity = 1;
	self->position.y -= 50;

	//Collider
	self->collision_offset = vector3d(5, 5, 5);
	slog("Enemy1 Ent Created");
	return self;
}

void enemy3_think(Entity *self){
	enemy2_move(self);
}

void enemy3_move(Entity *self){
	Vector3D player = player_active()->position;
	Vector3D pos = self->position;
	float distancex = abs(player.x - pos.x);
	float distancey = abs(player.y - pos.y);

	if (distancex > 50){
		if (pos.x < player.x){
			self->position.x += 0.09;
		}
		if (pos.x > player.x){
			self->position.x -= 0.09;
		}
		return;
	}
	if (distancey > 50){
		if (pos.y < player.y){
			self->position.y += 0.09;
		}
		if (pos.y > player.y){
			self->position.y -= 0.09;
		}
		return;
	}
	if (distancex > 30){
		if (pos.x < player.x){
			self->position.x += 0.09;
		}
		if (pos.x > player.x){
			self->position.x -= 0.09;
		}
		return;
	}
	if (distancey > 30){
		if (pos.y < player.y){
			self->position.y += 0.09;
		}
		if (pos.y > player.y){
			self->position.y -= 0.09;
		}
		return;
	}
	if (distancex <= 30){
		if (pos.x < player.x){
			self->position.x += 0.09;
		}
		if (pos.x > player.x){
			self->position.x -= 0.09;
		}
	}
	if (distancey <= 30){
		if (pos.y < player.y){
			self->position.y += 0.09;
		}
		if (pos.y > player.y){
			self->position.y -= 0.09;
		}
	}
	gfc_matrix_make_translation(self->modelMatrix, self->position);
}

void enemy3_collision(Entity *self, Entity *ent2){
	enemy3_attack(self, ent2);
	entity_free(self);
}

void enemy3_attack(Entity *self, Entity *ent2){
	ent2->health -= 15;
}