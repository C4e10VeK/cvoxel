#ifndef CVOXEL_GAME_H
#define CVOXEL_GAME_H

#include "utils/types.h"
#include "utils/macro.h"
#include "client/window/window.h"
#include "ecs/ecs.h"

typedef struct
{
	Window *wnd;
	ECS ecs;
	i32 tick;
} Game;

Game gameInit(Window *wnd);

void gameUpdate(Game *game);

CVOX_INLINE void mainGameLoop(Game *game)
{
	while (!windowIsClosed(game->wnd))
	{
		if (game->wnd->keys[GLFW_KEY_ESCAPE])
			windowClose(game->wnd);

		gameUpdate(game);

		windowPollEvents();
		windowSwapBuffers(game->wnd);
	}
}

#endif // CVOXEL_GAME_H