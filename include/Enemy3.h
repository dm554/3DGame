#ifndef __GF3D_ENEMY3_H__
#define __GF3D_ENEMY3_H__

#include "Entity.h"

Entity *enemy3_new();

void enemy3_think(Entity *self);

void enemy3_move(Entity *self);

void enemy3_collision(Entity *self, Entity *ent2);

void enemy3_attack(Entity *self, Entity *ent2);

#endif