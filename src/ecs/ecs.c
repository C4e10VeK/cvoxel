#include "ecs.h"
#include <assert.h>
#include <memory.h>

ECS ecsInit()
{
	return (ECS){0, 0};
}

Entity ecsNewEntity(ECS *ecs)
{
	(void) ecs;
	return UINT32_MAX;
}

void ecsFree(ECS *ecs)
{
	(void) ecs;
	return;
}
