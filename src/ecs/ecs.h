#ifndef CVOXEL_ECS_H
#define CVOXEL_ECS_H

#include <stdbool.h>
#include "../utils/types.h"
#include "../utils/bitset.h"

typedef u32 Entity;
#define MAX_ENTITIES 16
#define MAX_COMPONENTS COMPONENT_COUNT

enum Component
{
	TRANSFORM = 0,
	CAMERA,
	NAME,

	COMPONENT_COUNT
};

typedef struct
{
	void *components;
	size_t typeSize;
	size_t size;
} ComponentList;

typedef struct ECS
{
	ComponentList componentLists[COMPONENT_COUNT];

	Bitset usedComponentFlag[MAX_ENTITIES];
	Bitset flagEntities;
	size_t capacity;
	Entity nextEntity;
} ECS;

ECS ecsInit();

Entity ecsNewEntity(ECS *ecs);

bool ecsHasComponent(ECS *ecs, Entity entity, u32 component);

void *ecsAddComponent(ECS *ecs, Entity entity, u32 component, void *data);

void *ecsGetComponent(ECS *ecs, Entity entity, u32 component);

void ecsFree(ECS *ecs);

#endif // CVOXEL_ECS_H
