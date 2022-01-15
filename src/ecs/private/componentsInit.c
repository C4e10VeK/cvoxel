#include "componentsInit.h"
#include <stdlib.h>

#include "../components/transform.h"
#include "../components/camera.h"
#include "../components/name.h"

#define _CVOX_DECL_INIT(name, type) void init##name##C(ECS *ecs)\
	{\
		ComponentList *list = &ecs->componentLists[type];\
		list->components = calloc(MAX_ENTITIES, sizeof(name));\
		list->typeSize = sizeof(name);\
		list->capacity = MAX_ENTITIES;\
	}

_CVOX_DECL_INIT(Transform, TRANSFORM);
_CVOX_DECL_INIT(Camera, CAMERA);
_CVOX_DECL_INIT(Name, NAME);
