#include "../include/boid.h"

void createBoid(Boid **boids, short *boidCount, float x, float y) {
	*boids = SDL_realloc(*boids, (*boidCount + 1) * sizeof(Boid));
    Boid *boid = &(*boids)[*boidCount];
    (*boidCount)++;

	boid->verticesPosition[0].position.x = x;
	boid->verticesPosition[0].position.y = y - BOID_H;
	boid->verticesPosition[1].position.x = x - BOID_W / 2;
	boid->verticesPosition[1].position.y = y;
	boid->verticesPosition[2].position.x = x + BOID_W / 2;
	boid->verticesPosition[2].position.y = y;
	for (int i = 0; i < 3; ++i) {
		boid->verticesPosition[i].color.r = 0;
		boid->verticesPosition[i].color.g = 0;
		boid->verticesPosition[i].color.b = 255;
		boid->verticesPosition[i].color.a = SDL_ALPHA_OPAQUE;
	}

	boid->dir = 270.0;

	boid->mid.x = (boid->verticesPosition[0].position.x + boid->verticesPosition[1].position.x + boid->verticesPosition[2].position.x) / 3.0;
	boid->mid.y = (boid->verticesPosition[0].position.y + boid->verticesPosition[1].position.y + boid->verticesPosition[2].position.y) / 3.0;
}

void rotateBoid(Boid *boid, float angle) {
	float rad = angle * M_PI / 180.0;
	float c = SDL_cosf(rad);
	float s = SDL_sinf(rad);

	for (int i = 0; i < 3; ++i) {
		float translateX = boid->verticesPosition[i].position.x - boid->mid.x;
		float translateY = boid->verticesPosition[i].position.y - boid->mid.y;

		float newX = translateX * c - translateY * s;
		float newY = translateX * s + translateY * c;

		boid->verticesPosition[i].position.x = newX + boid->mid.x;
		boid->verticesPosition[i].position.y = newY + boid->mid.y;
	}

	boid->dir += angle;
}

