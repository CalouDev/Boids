#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "../include/boid.h"
#include "../include/utils.h"

#define WIN_W 1280
#define WIN_H 640
#define BOID_SPD 0.01

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

short boidCount = 0;
Boid *boids = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;
	if (!SDL_Init(SDL_INIT_AUDIO)) return SDL_APP_FAILURE;
	if (!TTF_Init()) return SDL_APP_FAILURE;

    window = SDL_CreateWindow("Boïds simulation", WIN_W, WIN_H, SDL_WINDOW_OPENGL);
    if (!window) return SDL_APP_FAILURE;

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) return SDL_APP_FAILURE;

	boids = SDL_calloc(10, sizeof(Boid));

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
	SDL_free(boids);
	boids = NULL;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	switch (event->type) {
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event->button.button == SDL_BUTTON_LEFT) {
				createBoid(&boids, &boidCount, event->button.x, event->button.y);
			}
		default:
			break;
	}

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);	

	for (int i = 0; i < boidCount; ++i) {
		//rotateBoid(&boids[i], 0.0003);
		if (boids[i].dir >= 360) boids[i].dir = 0;
		for (int j = 0; j < 3; ++j) {
			boids[i].verticesPosition[j].position.x += BOID_SPD * cos(toRad(boids[i].dir));
			boids[i].verticesPosition[j].position.y += BOID_SPD * sin(toRad(boids[i].dir));
		}
		SDL_RenderGeometry(renderer, NULL, boids[i].verticesPosition, 3, NULL, 3);
	}

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}
