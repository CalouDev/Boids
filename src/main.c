#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "../include/boid.h"
#include "../include/utils.h"

#define WIN_W 1280
#define WIN_H 640

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

short boidCount = 0;
Boid *boids = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO) || !SDL_Init(SDL_INIT_AUDIO) || !TTF_Init()) return SDL_APP_FAILURE;

    window = SDL_CreateWindow("Boïds", WIN_W, WIN_H, SDL_WINDOW_OPENGL);
    if (!window) return SDL_APP_FAILURE;

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        SDL_Log("Erreur: Impossible de créer le contexte OpenGL (%s)\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) return SDL_APP_FAILURE;

	boids = SDL_calloc(1, sizeof(Boid));

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

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderRect(renderer, &(SDL_FRect){20, 20, WIN_W - 320, WIN_H - 40});

	for (int i = 0; i < boidCount; ++i) {
		regulatedAngle(boids[i].dir);
	
		avoidBorder(&boids[i], 20, WIN_W - 300, 20, WIN_H - 20);

		for (int j = 0; j < 3; ++j) {
			boids[i].verticesPosition[j].position.x += BOID_SPD * SDL_cosf(toRad(boids[i].dir));
			boids[i].verticesPosition[j].position.y += BOID_SPD * SDL_sinf(toRad(boids[i].dir));
		}

		boids[i].mid.x = (boids[i].verticesPosition[0].position.x + boids[i].verticesPosition[1].position.x + boids[i].verticesPosition[2].position.x) / 3.0;
		boids[i].mid.y = (boids[i].verticesPosition[0].position.y + boids[i].verticesPosition[1].position.y + boids[i].verticesPosition[2].position.y) / 3.0;

		SDL_RenderGeometry(renderer, NULL, boids[i].verticesPosition, 3, NULL, 3);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		for (int k = 0; k < 3; ++k) drawCircle(renderer, boids[i].verticesPosition[k].position.x, boids[i].verticesPosition[k].position.y, AVOID_RANGE);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		drawCircle(renderer, boids[i].mid.x, boids[i].mid.y, DETECTION_RANGE);
	}

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

