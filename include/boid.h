#ifndef BOID
#define BOID

#define BOID_W 10
#define BOID_H 20

#include <math.h>
#include <SDL3/SDL.h>

typedef struct {
	SDL_Vertex verticesPosition[3];
	float dir;
	SDL_Point mid;
} Boid;

void createBoid(Boid **boids, short *boidCount, float x, float y);
void rotateBoid(Boid *boid, float angle);

#endif
