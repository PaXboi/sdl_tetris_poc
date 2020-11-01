#include <SDL2/SDL.h>

int game_menu(SDL_Window* pwin) {
	SDL_Renderer* renderer = SDL_CreateRenderer(pwin, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* placeholder_surface = SDL_LoadBMP("placeholder.bmp");
	SDL_Texture* placeholder_tex = SDL_CreateTextureFromSurface(renderer, placeholder_surface);
	
	while (1) {
		SDL_Event pevent;
		if (SDL_PollEvent(&pevent)) {
			if (pevent.type == SDL_QUIT) {
				return 0;
			}
		}
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, placeholder_tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	return 0;
}
