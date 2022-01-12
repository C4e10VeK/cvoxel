#include <stdio.h>
#include <stdlib.h>

#include <glad/gl.h>

#include <cglm/types-struct.h>

#include "client/window/window.h"
#include "game.h"

#define VERT_PATH "../res/shaders/vert.glsl"
#define FRAG_PATH "../res/shaders/frag.glsl"
#define TEXTURE_PATH "../res/textures/brick.png"

#define WORLD_VOL 4096

int main()
{
	Window wnd;

	if (!windowInit(&wnd, (WindowParams){800, 500, true}, "cvoxel"))
		abort();
	
	Game game = gameInit(&wnd);

	mainGameLoop(&game);

	gameFree(&game);
	windowDestroy(&wnd);

	return 0;
}
