#ifndef __GF3D_CUBE_H__
#define __GF3D_CUBE_H__

#include "Entity.h"

Entity *cube_new();

void cube_think(Entity *self);

void cube_collide(Entity *self, Entity *ent2);

void cube_powerups(Entity *ent2);

void cube_speed(int timer, float speed);

void cube_low_gravity(int timer, float new_gravity);

void cube_health(int amount);

void cube_stamina(int amount);

void cube_invincible(int timer);
#endif