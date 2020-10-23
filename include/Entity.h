#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf3d_vgraphics.h"
#include "gf3d_model.h"
#include "simple_logger.h"

typedef struct Entity_S{
	
	Uint8		_inuse;
	Vector3D	position;
	char		*model;
	Matrix4		modelMatrix;
	char		name;

	void(*think)(struct Entity_S *self);

}Entity;

void entity_manager_init(Uint32 maxEntities);
void entity_manager_close();
void entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer);
void entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer);

int entity_return_num();

Entity *entity_new();

Entity entity_update(Entity *self);
Entity entity_update_all(Entity *self);
Entity entity_free(Entity *self);


#endif