#include "gfc_matrix.h"
#include "gf3d_vgraphics.h"
#include "Player.h"

#include <string.h>

Matrix4 gf3d_camera = {0};

static Vector3D cam_position;

void gf3d_camera_get_view(Matrix4 *view)
{
    if (!view)return;
    memcpy(view,gf3d_camera,sizeof(Matrix4));
}

void gf3d_camera_set_view(Matrix4 *view)
{
    if (!view)return;
    memcpy(gf3d_camera,view,sizeof(Matrix4));
}

void gf3d_camera_look_at(
    Vector3D position,
    Vector3D target,
    Vector3D up
)
{
    gfc_matrix_view(
        gf3d_camera,
        position,
        target,
        up
    );
}

void gf3d_camera_set_position(Vector3D position)
{
    gf3d_camera[0][3] = position.x;
    gf3d_camera[1][3] = position.y;
    gf3d_camera[2][3] = position.z;
}

void gf3d_camera_move(Vector3D move)
{
    gf3d_camera[0][3] += move.x;
    gf3d_camera[1][3] += move.y;
    gf3d_camera[2][3] += move.z;
}

Vector3D gf3d_camera_get_position(){
	return vector3d(gf3d_camera[0][3], gf3d_camera[1][3], gf3d_camera[2][3]);
}

void gf3d_camera_update_position(){
	Entity *player = player_active();
	Vector3D camera = cam_position;
	float distancex = abs(player->position.x - camera.x);
	float distancey = abs(player->position.y - camera.y);
	cam_position.z = player->position.z + 20;
	
	if (player->position.x > camera.x){
		slog("camera moving");
		cam_position.x += 0.1;
	}
	if (camera.x > player->position.x){
		slog("camera moving");
		cam_position.x -= 0.1;
	}

	if (distancey > 40){
		if (player->position.y > camera.y){
			slog("camera moving");
			cam_position.y += 0.1;
		}
		if (camera.y > player->position.y){
			slog("camera moving");
			cam_position.y -= 0.1;
		}
	}

	if (distancey < 30){
		if (player->position.y > camera.y){
			slog("camera moving");
			cam_position.y -= 0.1;
		}
		if (camera.y > player->position.y){
			slog("camera moving");
			cam_position.y += 0.1;
		}
	}

	cam_position.z = player->position.z + 20;
	gf3d_vgraphics_set_camera_position(cam_position, player->position);
	
	//slog("%f, %f, %f", camera.x, camera.y, camera.z);
}

/*eol@eof*/
