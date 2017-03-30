#ifndef BALL_H_
#define BALL_H_

#include "geometry.h"

typedef struct Ball {
	float radius;
	int full;
	Color3D color;
	Point position;
	Vector vector;
} Ball;


Ball createBall(float radius, int full, Color3D color, Point position, Vector vector);

void drawBall(Ball ball);

#endif