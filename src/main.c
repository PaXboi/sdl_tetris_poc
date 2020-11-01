#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

/* Header containing compile time defaults. */
#include "defs/defaults.h"

#include "menu.h"

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
			SDL_Log("FATAL: Could not init SDL, SDL reports: %s", SDL_GetError());
			return 1;
		}
	
	SDL_Window* pwin = SDL_CreateWindow(
	PRIMARY_WINDOW_TITLE,
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	1, /* Just 1 pixel tall and wide here just because we need to create a window. */
	1, /* We are going to resize it soon. */
	SDL_WINDOW_OPENGL);
	
	if (pwin == NULL) {
		SDL_Log("FATAL: Could not create primary window, SDL reports: %s", SDL_GetError());
		return 1;
	}
	
	int pwin_displayidex = SDL_GetWindowDisplayIndex(pwin);
	if (pwin_displayidex < 0) {
		SDL_Log("FATAL: Could not get display index of primary window, SDL reports: %s", SDL_GetError());
		return 1;
	}

	/* Get size of screen (X, Y) our window is on and set the size of the 
	 * window to be (X*DEFAULT_RES_MULTIPLY, Y*DEFAULT_RES_MULTIPLY).
	 * Also center it.  */
	SDL_DisplayMode pwin_display;
	if (SDL_GetCurrentDisplayMode(pwin_displayidex, &pwin_display) != 0) {
		SDL_Log("ERROR: Could not get display mode for display %d, SDL reports: %s", pwin_displayidex, SDL_GetError());
		SDL_Log("Using fallback resolution.");
		pwin_display.w = RES_FALLBACK_X;
		pwin_display.h = RES_FALLBACK_Y;
	}
	SDL_SetWindowSize(pwin, pwin_display.w * RES_MULTIPLY, pwin_display.h * RES_MULTIPLY);
	SDL_SetWindowPosition(pwin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	
	if (game_menu(pwin) != 0) {
		SDL_Log("Could not create game menu.");
		return 1;
	}
	
	SDL_DestroyWindow(pwin);
	SDL_Quit();
	return 0;
}
