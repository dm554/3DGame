#include "Enemy2.h"
#include "Player.h"
#include "SDL.h"

static Vector3D target_position;
Entity *enemy2_new(){

	Entity *self;
	self = entity_new();
	self->model = gf3d_model_load("dino");
	gfc_matrix_identity(self->modelMatrix);
	self->think = enemy2_think;
	self->collide = enemy2_collision;
	self->velocity = 0.08;
	//STATS
	self->velocity = 1;
	self->position.x += 33;
	self->position.y += 120;

	//Collider
	self->collision_offset = vector3d(5, 5, 5);
	slog("Enemy1 Ent Created");
	return self;
}

void enemy2_think(Entity *self){
	enemy2_move(self);
}

void enemy2_move(Entity *self){
	Vector3D player = player_active()->position;
	Vector3D pos = self->position;
	float distancex = abs(player.x - pos.x);
	float distancey = abs(player.y - pos.y);

	if (distancex > 30){
		if (pos.x < player.x){
			self->position.x += 0.08;
		}
		if (pos.x > player.x){
			self->position.x -= 0.08;
		}
	}
	if (distancey > 30){
		if (pos.y < player.y){
			self->position.y += 0.08;
		}
		if (pos.y > player.y){
			self->position.y -= 0.08;
		}
	}
	if (distancex <= 30){
		if (pos.x < player.x){
			self->position.x += 0.25;
		}
		if (pos.x > player.x){
			self->position.x -= 0.25;
		}
	}
	if (distancey <= 30){
		if (pos.y < player.y){
			self->position.y += 0.25;
		}
		if (pos.y > player.y){
			self->position.y -= 0.25;
		}
	}
	gfc_matrix_make_translation(self->modelMatrix, self->position);
}

void enemy2_collision(Entity *self, Entity *ent2){
	enemy2_attack(self, ent2);
	entity_free(self);
}

void enemy2_attack(Entity *self, Entity *ent2){
	if (!ent2->invincible){
		ent2->health -= 15;
	}
}