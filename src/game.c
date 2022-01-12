#include "game.h"

#include <assert.h>
#include <glad/gl.h>

Game gameInit(Window *wnd)
{
	Game res;

	assert(wnd && "window is NULL\n");

	res.wnd = wnd;
	res.tick = 0;

	res.ecs = ecsInit();

	return res;
}

void gameUpdate(Game *game)
{
	assert(game);

	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gameFree(Game *game)
{
	assert(game);
	
	ecsFree(&game->ecs);
	game->tick = 0;
	game->wnd = NULL;
}
