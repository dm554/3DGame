#include "simple_logger.h"
#include "MainMenu.h"
#include "Menu.h"



Menu *main_menu_new(){
	Menu *self;
	//self = menu_new();
	self = (Menu*)gfc_allocate_array(sizeof(Menu), 1);
	
	self->cursorPoint = 1;
	self->cursorPointTotal = 3;
	self->backPosition = vector2d(0, 0);
	self->cursorPoint_1 = vector2d(0, 25);
	self->cursorPoint_2 = vector2d(0, 85);
	self->cursorPoint_3 = vector2d(0, 140);
	self->cursorPostion = self->cursorPoint_1;
	self->think = main_menu_think;
	self->backsprite = gf3d_sprite_load("images/Mainmenu2.png", -1, -1, 0);
	self->cursorSprite = gf3d_sprite_load("images/cursor.png", -1, -1, 0);
	slog("Menu made");
	menu_set_active(self);
	return self;
	
}

void main_menu_think(Menu *self){

	main_menu_option_select(self->select, self);

}

void main_menu_option_select(int select, Menu *self){
	switch (select){
	case 0:
		break;
	case 1:
		main_menu_option_1(self);
		break;
	case 2:
		main_menu_option_2(self);
		break;
	case 3:
		main_menu_option_3(self);
		break;
	}
}

void main_menu_option_1(Menu *self){
	slog("MM1");
	self->select = 0;
	SceneController(2);
	//menu_free(menu_get_active());
}

void main_menu_option_2(Menu *self){
	
	//menu_free(self);
}

void main_menu_option_3(Menu *self){
	//close game
	menu_free(menu_get_active());
}