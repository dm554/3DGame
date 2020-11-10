#ifndef __GF3D_PLAYER_H__
#define __GF3D_PLAYER_H__

#include "Entity.h"
#include "gf3d_camera.h"

static Entity *THE_PLAYER;

Entity *player_new();

void player_think(Entity *self);

void player_input(Entity *self);

void player_move(Entity *self, Uint8 *buttons);

void player_ability(Entity *self, Uint8 *buttons);

void player_sprint(Entity *self);

void player_jump(Entity *self);

void player_dodge(Entity *self);

void player_collision(Entity *self, Entity *ent2);

void player_attack(Entity *self, Entity *ent2);

void player_attack_command(Entity *self, Uint8 *buttons);

void player_gravity(Entity *self);

Entity *player_active();

#endif