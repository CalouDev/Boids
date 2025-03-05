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

void drawCircle(SDL_Renderer *renderer, float centerX, float centerY, float radius) {
    int diameter = (radius * 2);
    float x = (radius - 1);
    float y = 0;
    float tx = 1;
    float ty = 1;
    float error = (tx - diameter);

    while (x >= y) {
        SDL_RenderPoint(renderer, centerX + x, centerY - y);
        SDL_RenderPoint(renderer, centerX + x, centerY + y);
        SDL_RenderPoint(renderer, centerX - x, centerY - y);
        SDL_RenderPoint(renderer, centerX - x, centerY + y);
        SDL_RenderPoint(renderer, centerX + y, centerY - x);
        SDL_RenderPoint(renderer, centerX + y, centerY + x);
        SDL_RenderPoint(renderer, centerX - y, centerY - x);
        SDL_RenderPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
	}
}
