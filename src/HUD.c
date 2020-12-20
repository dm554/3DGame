#include <SDL.h>
#include <SDL_ttf.h>
#include "HUD.h"

HUD *hud_new(HUD *hud){

	
	
}

void hud_update(HUD *hud){

	hud->health = gf3d_sprite_load("images/healthbar.png", -1, -1, 0);
	hud->healthbar = gf3d_sprite_load("images/hbar.png", -1, -1, 0);

	hud->stamina = gf3d_sprite_load("images/staminabar.png", -1, -1, 0);
	hud->staminabar = gf3d_sprite_load("images/stbar.png", -1, -1, 0);

	hud->special = gf3d_sprite_load("images/specialbar.png", -1, -1, 0);
	hud->specialbar = gf3d_sprite_load("images/sbar.png", -1, -1, 0);

	Entity *player = player_active();
	float health = player->health;
	float stamina = player->stamina;
	float meter = player->meter;
	
	int increment = 2;
	
	hud->barposition.x = (-50 - ((100 - health) * increment));
	hud->barposition.y = (-50 - ((100 - stamina) * increment));
	hud->barposition.z = (-50 - ((100 - meter) * increment));

}



