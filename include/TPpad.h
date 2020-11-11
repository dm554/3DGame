#ifndef __GF3D_TPPAD_H__
#define __GF3D_TPPAD_H__

#include "Entity.h"

Entity *telpad_new();

void telpad_think(Entity *self);

void telpad_collide(Entity *self, Entity *ent2);

#endif