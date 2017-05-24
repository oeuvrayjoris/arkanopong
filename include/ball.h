#ifndef BALL_H_
#define BALL_H_

#include "geometry.h"
#include "bar.h"
#include "brick.h"

typedef struct Ball {
	float radius;
	int full;
	Color3D color;
	Point position;
	Vector vector;
} Ball;


Ball createBall(float radius, int full, Color3D color, Point position, Vector vector);

void drawBall(Ball ball);

int collisionWithBar(Ball *ball, Bar bar, int onTop);

int collisionWithWindow(Ball ball);

int collisionWithBrick(Ball *ball, Brick *brick, Bar *bar1, Bar *bar2);

#endif