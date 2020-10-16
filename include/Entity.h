#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf3d_model.h"

typedef struct Entity_S{
	
	Uint8		_inuse;
	Vector3D	position;
	Model		*model;

	void(*think)(struct Entity_S *self);

}Entity;

void entity_manager_init(Uint32 maxEntities);
void entity_manager_close();

Entity *entity_new();

Entity entity_update(Entity *self);
Entity entity_update_all(Entity *self);
Entity entity_free(Entity *self);

#endif