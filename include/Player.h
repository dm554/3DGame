#ifndef __GF3D_PLAYER_H__
#define __GF3D_PLAYER_H__

#include "Entity.h"

static Entity *THE_PLAYER;

Entity *player_new();

void player_think(Entity *self);

void player_input(Entity *self);

Entity *player_active();

#endif