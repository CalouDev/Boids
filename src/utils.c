#include "../include/utils.h"

float toRad(float degree) {
	return degree * SDL_PI_F / 180.0;
}

float regulatedAngle(float degree) {
	float regulatedAngle = degree;

	if (regulatedAngle >= 360.0) regulatedAngle -= 360.0;
	else if (regulatedAngle < 0) regulatedAngle += 360.0;

	return regulatedAngle;
}

float pointsDist(float x1, float y1, float x2, float y2) {
	return SDL_sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

SDL_FPoint angleToVec(float angle) {
	SDL_FPoint dirVec;

	float rad = toRad(angle);

	dirVec.x = SDL_cosf(rad);
	dirVec.y = SDL_sinf(rad);

	return dirVec;
}
