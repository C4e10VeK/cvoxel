#ifndef CVOXEL_GAME_H
#define CVOXEL_GAME_H

#include "utils/types.h"
#include "client/window/window.h"
#include "ecs/ecs.h"

typedef struct
{
	Window *wnd;
	Ecs ecs;
	i32 tick;
} Game;

Game gameInit(Window *wnd);

void gameUpdate(Game *game);

#endif // CVOXEL_GAME_H