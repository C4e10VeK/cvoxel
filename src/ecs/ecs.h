#ifndef CVOXEL_ECS_H
#define CVOXEL_ECS_H

#include "../utils/types.h"

typedef u32 Entity;
#define MAX_ENTITIES 500

enum Component
{
	TRANSFORM = 0,
	CAMERA,

	COMPONENT_COUNT
};

typedef struct ECS
{
	size_t capacity;
	Entity nextFreeEntity;
} ECS;

ECS ecsInit();

Entity ecsNewEntity(ECS *ecs);

void ecsFree(ECS *ecs);

#endif // CVOXEL_ECS_H
