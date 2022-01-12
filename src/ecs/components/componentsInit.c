#include "componentsInit.h"
#include <stdlib.h>

#include "../../utils/macro.h"

#include "transform.h"
#include "camera.h"
#include "name.h"

#include "../ecs.h"

CVOX_STATIC_INLINE void initTransformC(ECS *ecs)
{
	ComponentList *list = &ecs->componentLists[TRANSFORM];
	list->components = calloc(MAX_ENTITIES, sizeof(Transform));
	list->typeSize = sizeof(Transform);
	list->capacity = MAX_ENTITIES;
}

CVOX_STATIC_INLINE void initCameraC(ECS *ecs)
{
	ComponentList *list = &ecs->componentLists[CAMERA];
	list->components = calloc(MAX_ENTITIES, sizeof(Camera));
	list->typeSize = sizeof(Camera);
	list->capacity = MAX_ENTITIES;
}

CVOX_STATIC_INLINE void initNameC(ECS *ecs)
{
	ComponentList *list = &ecs->componentLists[NAME];
	list->components = calloc(MAX_ENTITIES, sizeof(Name));
	list->typeSize = sizeof(Name);
	list->capacity = MAX_ENTITIES;
}

void initComponets(void *ecs)
{
	ECS *e = (ECS *)ecs;

	initTransformC(e);
	initCameraC(e);
	initNameC(e);
}