#ifndef __GF3D_ENEMY1_H__
#define __GF3D_ENEMY1_H__

#include "Entity.h"

Entity *enemy1_new();

void enemy1_think(Entity *self);

void enemy1_move(Entity *self);

void enemy1_collision(Entity *self, Entity *ent2);

void enemy1_attack(Entity *self, Entity *ent2);

void enemy_gravity(Entity *self);
#endif