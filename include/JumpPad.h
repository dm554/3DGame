#ifndef __GF3D_JUMPPAD_H__
#define __GF3D_JUMPPAD_H__

#include "Entity.h"

Entity *jumppad_new();

void jumppad_think(Entity *self);

void jumppad_collide(Entity *self, Entity *ent2);

#endif