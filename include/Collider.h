#ifndef __GF3D_COLLIDER_H__
#define __GF3D_COLLIDER_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf3d_vgraphics.h"
#include "gf3d_model.h"
#include "simple_logger.h"
#include "gfc_matrix.h"

typedef struct Collider_S{

	Uint8		_inuse;
	Vector3D	position;
	Vector3D	rotation;
	Vector3D	offset;

}Collider;

#endif