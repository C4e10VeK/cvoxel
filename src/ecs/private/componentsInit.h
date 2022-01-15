#ifndef CVOXEL_COMPONENTS_INIT_H
#define CVOXEL_COMPONENTS_INIT_H

#include "../../utils/macro.h"
#include "../ecs.h"

#define _CVOX_ECS_DECL_C(name) ({ extern void init##name##C(ECS *);\
	init##name##C(ecs); })

CVOX_STATIC_INLINE void initComponets(ECS *ecs)
{
	_CVOX_ECS_DECL_C(Transform);
	_CVOX_ECS_DECL_C(Camera);
	_CVOX_ECS_DECL_C(Name);
}

#endif