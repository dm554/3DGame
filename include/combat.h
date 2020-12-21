#ifndef __GFC_COMBAT_H__
#define __GFC_COMBAT_H__

#include "Entity.h"

static int input_1;
static int input_2;
static int input_3;

void combat_engage(Entity *player, int player_input);

void combo_router(Entity *player, int attack);

void combat_hit(Entity *player, float hitstun, float knockback, int ex);

void knockback_applier(float knockback, Entity *target);

void input_clear();

void input_counter();

#endif