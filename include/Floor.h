#ifndef __GF3D_FLOOR_H__
#define __GF3D_FLOOR_H__

#include "Entity.h"

Entity *floor_new();

void floor_think(Entity *self);

void floor_collide(Entity *self, Entity *ent2);

#endif