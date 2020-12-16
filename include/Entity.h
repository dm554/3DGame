#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf3d_vgraphics.h"
#include "gf3d_model.h"
#include "simple_logger.h"
#include "gfc_matrix.h"
#include "Collider.h"

typedef struct Entity_S{
	
	Uint8		_inuse;
	Vector3D	position;
	Vector3D	rotation;
	Vector3D	collision_offset;
	float		gravity;
	float		starting_height;
	float		health;
	float		stamina;
	float		meter;
	float		aoe_range;
	float		velocity;
	int			jumptime;
	int			dashtime;
	int			speedPad;
	int			speedUp;
	float		sprintFactor;
	int			invincible;
	float		hitstun;
	char		*model;
	Matrix4		modelMatrix;
	char		name;
	Uint8		angle;
	Uint8		state; //1 = Idle, 2 = Moving, 3 = Jumping, 4 = Dashing 

	void(*think)(struct Entity_S *self);
	void(*collide)(struct Entity_S *self);

}Entity;

void entity_manager_init(Uint32 maxEntities);
void entity_manager_close();

void entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer);
void entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer);
void entity_update_all();

void entity_collision_checker();
void entity_collide(Entity *ent1, Entity *ent2);
int entity_collide_calc(Entity *ent1, Entity *ent2);


int entity_return_num();

Entity *entity_new();


Entity entity_update(Entity *self);
Entity entity_free(Entity *self);


#endif