#ifndef __HUD_H__
#define __HUD_H__

#include "Player.h"
#include "gf3d_sprite.h"

typedef struct HUD_S{

	Vector3D *position;
	Vector3D barposition;
	Sprite *health;
	Sprite *healthbar;
	Sprite *stamina;
	Sprite *staminabar;
	Sprite *special;
	Sprite *specialbar;



}HUD;

HUD *hud_new(HUD *hud);

void hud_update(HUD *hud);

void hud_draw(Vector3D *position, Entity *player);


#endif