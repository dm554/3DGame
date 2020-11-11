#ifndef __GF3D_SPEEDPAD_H__
#define __GF3D_SPEEDPAD_H__

#include "Entity.h"

Entity *speedpad_new();

void speedpad_think(Entity *self);

void speedpad_collide(Entity *self, Entity *ent2);

#endif