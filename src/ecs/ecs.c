#include "ecs.h"
#include "../utils/macro.h"
#include <assert.h>
#include <memory.h>
#include <string.h>

#include "components/componentsInit.h"
#include "components/name.h"

ECS ecsInit()
{
	ECS res;

	memset(res.componentLists, 0, COMPONENT_COUNT * sizeof(ComponentList));
	memset(res.usedComponentFlag, 0, MAX_ENTITIES * sizeof(Bitset));

	res.flagEntities = bitsetInit();
	bitsetAlloc(&res.flagEntities, MAX_ENTITIES);

	res.capacity = MAX_ENTITIES;
	res.nextEntity = 0;

	initComponets(&res);

	return res;
}

CVOX_STATIC_INLINE void _setNextEntity(ECS *ecs)
{
	for (size_t i = 0; i < ecs->flagEntities.size; i++)
	{
		if (!bitsetTest(&ecs->flagEntities, i))
		{
			ecs->nextEntity = i;
			break;
		}
	}
}

Entity ecsNewEntity(ECS *ecs)
{
	Entity res = ecs->nextEntity;

	if (!ecs->usedComponentFlag[res].data)
		bitsetAlloc(&ecs->usedComponentFlag[res], MAX_COMPONENTS);

	bitsetSet(&ecs->flagEntities, res);
	bitsetSet(&ecs->flagEntities, 1);

	_setNextEntity(ecs);

	return res;
}

bool ecsHasComponent(ECS *ecs, Entity entity, u32 component)
{
	assert(ecs);

	return bitsetTest(&ecs->usedComponentFlag[entity], component);
}

void *ecsAddComponent(ECS *ecs, Entity entity, u32 component, void *data)
{
	assert(ecs);

	if (ecsHasComponent(ecs, entity, component))
		return (void*)(0 - 1);

	ComponentList *list = &ecs->componentLists[component];
	
	if (data != NULL)
		memcpy(list->components + entity * list->typeSize, data, list->typeSize);
	
	bitsetSet(&ecs->usedComponentFlag[entity], component);
	
	return (list->components + entity * list->typeSize);
}

void *ecsGetComponent(ECS *ecs, Entity entity, u32 component)
{
	assert(ecsHasComponent(ecs, entity, component));

	return (ecs->componentLists[component].components + entity * ecs->componentLists->typeSize);
}

void ecsFree(ECS *ecs)
{
	assert(ecs);
	bitsetFree(&ecs->flagEntities);
	for (size_t i = 0; i < MAX_ENTITIES; i++)
		bitsetFree(&ecs->usedComponentFlag[i]);
		
	for (size_t i = 0; i < MAX_COMPONENTS; i++)
		free(ecs->componentLists[i].components);
}
