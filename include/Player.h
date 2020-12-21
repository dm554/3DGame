#ifndef __GF3D_PLAYER_H__
#define __GF3D_PLAYER_H__

#include "Entity.h"
#include "gf3d_camera.h"

static Entity *THE_PLAYER;

static Entity *target;

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

void player_stat_reset(Entity *self);

void player_increment(Entity *self);

void player_attack_rise(Entity *self, float range);

void player_attack_stun(Entity *self, float range);

void player_attack_succ(Entity *self, float range);

void player_ability_chi(Entity *self);

void player_ability_heal(Entity *self);

Entity *player_active();

Entity *player_target();

void player_aoe_checker(Entity *self, float range, float knockback, float hitstun, float knockup);

int player_aoe_range_check(Entity *self, Entity *enemy, float maxRange);


#endif