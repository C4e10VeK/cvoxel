#include "game.h"

#include <assert.h>
#include <glad/gl.h>

#define UNUSED(s) ((void)s)

Game gameInit(Window *wnd)
{
	Game res;

	assert(wnd && "window is NULL\n");

	res.wnd = wnd;
	res.tick = 0;

	ecsInit(&res.ecs);

	return res;
}

void gameUpdate(Game *game)
{
	UNUSED(game);

	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
