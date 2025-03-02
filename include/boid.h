#ifndef BOID
#define BOID

#include <math.h>
#include <SDL3/SDL.h>

#define BOID_W 10
#define BOID_H 20
#define BOID_SPD 0.09
#define AVOID_RANGE 4

typedef struct {
	SDL_Vertex verticesPosition[3];
	float dir;
	SDL_FPoint mid;
} Boid;

void createBoid(Boid **boids, short *boidCount, float x, float y);
void rotateBoid(Boid *boid, float angle);
void avoidBorder(Boid *boid, float x1, float x2, float y1, float y2);

#endif
