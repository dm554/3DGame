#ifndef __GF3D_PLAYER_H__
#define __GF3D_PLAYER_H__

#include "Entity.h"

Entity *player_new();

void player_think(Entity *self);

#endif