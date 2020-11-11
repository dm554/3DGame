#ifndef __GF3D_ENEMY2_H__
#define __GF3D_ENEMY2_H__

#include "Entity.h"

Entity *enemy2_new();

void enemy2_think(Entity *self);

void enemy2_move(Entity *self);

void enemy2_collision(Entity *self, Entity *ent2);

void enemy2_attack(Entity *self, Entity *ent2);

#endif