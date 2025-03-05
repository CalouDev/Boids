#ifndef UTILS
#define UTILS

#include <SDL3/SDL.h>

float toRad(float degree);
float regulatedAngle(float degree);
float pointsDist(float x1, float y1, float x2, float y2);
void drawCircle(SDL_Renderer *renderer, float centerX, float centerY, float radius);

#endif
