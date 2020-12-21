#include <SDL_image.h>
#include <stdlib.h>
#include "SDL.h"
#include "simple_logger.h"
#include "Menu.h"
#include "MainMenu.h"
#include "gf3d_sprite.h"
#include "gfc_types.h"
//#include "PauseMenu.h"

static Menu *THE_MENU = NULL;
static int cursorTimer = 0;
static int buttonTimer = 0;
static int genUpdates = 0;

void menu_update(Menu *self){
	slog("cursor handler");
	cursor_handler(self);
	slog("draw");
	menu_draw(self);
	self->think(self);
}

void cursor_handler(Menu *self){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type){
			/* Look for a keypress */
		case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch (event.key.keysym.sym){
			case SDLK_UP:
				if (self->cursorPoint > 1){
					self->cursorPoint -= 1;
				}
				else{
					self->cursorPoint = 3;
				}
				break;
			case SDLK_DOWN:
				if (self->cursorPoint < self->cursorPointTotal){
					self->cursorPoint += 1;
				}
				else{
					self->cursorPoint = 1;
				}
				break;
			case SDLK_z:
				slog("OS");
					cursor_option_select(self);
				break;
			default:
				break;
			}
		}
	}
	cursor_set_position(self);
}

void cursor_set_position(Menu *self){
	if (cursorTimer < 3){
		cursorTimer++;
		return;
	}
	switch (self->cursorPoint){
		case 1:
			self->cursorPostion = self->cursorPoint_1;
			break;
		case 2:
			self->cursorPostion = self->cursorPoint_2;
			break;
		case 3:
			self->cursorPostion = self->cursorPoint_3;
			break;
	}
	cursorTimer = 0;
}

void cursor_option_select(Menu *self){
	
	switch (self->cursorPoint){
	case 1:
		self->select = 1;
		break;
	case 2:
		self->select = 2;
		break;
	case 3:
		self->select = 3;
		break;
	}

}

void menu_draw(Menu *self){
	slog("drawing");
	if (!self)return;
}

void menu_free(Menu *self){
	gf3d_sprite_free(self->backsprite);
	gf3d_sprite_free(self->cursorSprite);
	memset(self, 0, sizeof(Menu));
}

void menu_set_active(Menu *activeMenu){
	THE_MENU = activeMenu;
}

Menu *menu_get_active(){
	return THE_MENU;
}

int get_genUpdates(){
	return genUpdates;
}

void SceneController(int sceneNo){

	switch (sceneNo)
	{
	case 1:
		{
			Menu *mainmenu = main_menu_new();
		}
		genUpdates = 0;
		break;
		//Main Menu
	case 2:
		slog("Scene 2");
		genUpdates = 1;
		break;
		//Gameplay
	case 3:
		{
			//Menu *pausemenu = pause_menu_new();
		}
		genUpdates = 0;
		//Level Creator
		break;
	case 4:
		{
			//Menu *upgrademenu = upgrade_menu_new();
		}
		genUpdates = 0;
		break;
		//Load Level
	case 5:
		{
			//Menu *perkmenu = perk_menu_new();
		}
		//Perk Menu
		break;
	}
}