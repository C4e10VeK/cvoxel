#include <stdio.h>
#include <stdlib.h>

#include <glad/gl.h>

#include "client/window/window.h"
#include "game.h"

#define VERT_PATH "../res/shaders/vert.glsl"
#define FRAG_PATH "../res/shaders/frag.glsl"
#define TEXTURE_PATH "../res/textures/brick.png"

#define WORLD_VOL 4096

static void _mainGameLoop(Game *game)
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

int main()
{
	Window wnd;

	if (!windowInit(&wnd, (WindowParams){800, 500, true}, "cvoxel"))
		abort();
	
	Game game = gameInit(&wnd);

	_mainGameLoop(&game);

	return 0;
}
