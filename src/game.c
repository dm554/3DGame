#include <SDL.h>            
#include <stdlib.h>
#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"

#include "Entity.h"
#include "Player.h"
#include "Cube.h"

#include "Camera.h"

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 1;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
	Entity *dino;
	Entity *cube;
	Entity *floor;
	//Model *model;
    //Matrix4 modelMat;
    //Model *model2;
    //Matrix4 modelMat2;
    
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
    
    // main game loop
    slog("gf3d main loop begin");
	dino = player_new();
	cube = cube_new();
	//dino->model = gf3d_model_load("dino");
    //gfc_matrix_identity(dino->modelMatrix);
    //model2 = gf3d_model_load("dino");
    //gfc_matrix_identity(modelMat2);
    //gfc_matrix_make_translation(
     //       modelMat2,
       //     vector3d(10,0,0)
        //);
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
        
		entity_update_all();
		gf3d_camera_update_position();
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
        gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(),bufferFrame);
        commandBuffer = gf3d_command_rendering_begin(bufferFrame);

		entity_draw_all(bufferFrame, commandBuffer);

		//gf3d_model_draw(dino->model,bufferFrame,commandBuffer, dino->modelMatrix);
        //gf3d_model_draw(model2,bufferFrame,commandBuffer,modelMat2);
            
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
