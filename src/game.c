#include <SDL.h>            
#include <stdlib.h>
#include <SDL_ttf.h>
#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "SDL.h"   
#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_sprite.h"
#include "Entity.h"
#include "Player.h"
#include "Cube.h"
#include "Floor.h"
#include "JumpPad.h"
#include "SpeedPad.h"
#include "TPpad.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "HUD.h"

#include "Camera.h"



int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 1;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
	
	//Sprite *hud = NULL;
	//Sprite *hbar = NULL;
	Sprite *mouse = NULL;
	int mousex, mousey;
	Uint32 mouseFrame = 0;
	float frame = 0;
	HUD *hud = (HUD *)malloc(sizeof(HUD));

	Entity *dino;
	Entity *cube;
	Entity *cube1;
	Entity *cube2;
	Entity *cube3;
	Entity *cube4;
	Entity *floor;
	Entity *jumppad;
	Entity *speedpad;
	Entity *telpad;
	Entity *enemy1;
	Entity *enemy2;
	Entity *enemy3;
	//Model *model;
    //Matrix4 modelMat;
    Model *skybox;
    Matrix4 skyboxmat;

    
    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"-disable_validate") == 0)
        {
            validate = 0;
        }
    }
    
    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        validate                //validation
    );
	
	entity_manager_init(32);
    
	mouse = gf3d_sprite_load("images/pointer.png", 32, 32, 16);
	//hud = gf3d_sprite_load("images/healthbar.png", -1, -1, 0);
	//hbar = gf3d_sprite_load("images/hbar.png", -1, -1, 0);

	
    // main game loop
    slog("gf3d main loop begin");
	dino = player_new();
	floor = floor_new();
	//hud_new(hud);
	/*
	cube = cube_new(0, 155);
	cube1 = cube_new(1, 125);
	cube2 = cube_new(2, 95);
	cube3 = cube_new(3, 65);
	cube4 = cube_new(4, 35);
	
	jumppad = jumppad_new();
	speedpad = speedpad_new();
	telpad = telpad_new();
	*/
	
	enemy1 = enemy1_new();
	enemy2 = enemy2_new();
	enemy3 = enemy3_new();
	
	//dino->model = gf3d_model_load("dino");
    //gfc_matrix_identity(dino->modelMatrix);
    //skybox = gf3d_model_load("skybox");
    //gfc_matrix_identity(skyboxmat);
    //gfc_matrix_make_translation(
     //       modelMat2,
       //     vector3d(10,0,0)
        //);
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
        
		SDL_GetMouseState(&mousex, &mousey);
		entity_update_all();
		gf3d_camera_update_position();
		hud_update(hud);
		frame = frame + 0.05;
		if (frame >= 24)frame = 0;
		mouseFrame = (mouseFrame + 1) % 16;
		//gf3d_vgraphics_rotate_camera(0.001);
		
		/*
		gfc_matrix_rotate(
            player_active()->modelMatrix,
            player_active()->modelMatrix,
            0.002,
            vector3d(1,0,0));
		gfc_matrix_rotate(
            modelMat2,
            modelMat2,
            0.002,
            vector3d(0,0,1));
			*/

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
       
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_model_pipeline(), bufferFrame);
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(), bufferFrame);

		commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_model_pipeline());

		entity_draw_all(bufferFrame, commandBuffer);

		//gf3d_model_draw(dino->model,bufferFrame,commandBuffer, dino->modelMatrix);
        //gf3d_model_draw(skybox,bufferFrame,commandBuffer,skyboxmat);
		gf3d_command_rendering_end(commandBuffer);

		// 2D overlay rendering
		commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());

		//HUD Drawing
		gf3d_sprite_draw(hud->health, vector2d(-50, -20), vector2d(2, 2), 0, bufferFrame, commandBuffer);
		gf3d_sprite_draw(hud->healthbar, vector2d(hud->barposition.x, -20), vector2d(2, 2), 0, bufferFrame, commandBuffer);

		gf3d_sprite_draw(hud->stamina, vector2d(-50, 20), vector2d(2, 2), 0, bufferFrame, commandBuffer);
		gf3d_sprite_draw(hud->staminabar, vector2d(hud->barposition.y, 20), vector2d(2, 2), 0, bufferFrame, commandBuffer);

		gf3d_sprite_draw(hud->special, vector2d(-50, 60), vector2d(2, 2), 0, bufferFrame, commandBuffer);
		gf3d_sprite_draw(hud->specialbar, vector2d(hud->barposition.z, 60), vector2d(2, 2), 0, bufferFrame, commandBuffer);
		
		gf3d_sprite_draw(mouse, vector2d(mousex, mousey), vector2d(1, 1), mouseFrame, bufferFrame, commandBuffer);

		gf3d_command_rendering_end(commandBuffer);
            
        gf3d_vgraphics_render_end(bufferFrame);

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
