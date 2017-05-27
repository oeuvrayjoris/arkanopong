#ifndef BALL_H_
#define BALL_H_

#include "geometry.h"
#include "bar.h"
#include "brick.h"
#include "player.h"

typedef struct Ball {
	float radius;
	int full;
	int state;
	Color3D color;
	Point position;
	Vector vector;
} Ball;


Ball createBall(float radius, int full, int state, Color3D color, Point position, Vector vector);

void drawBall(Ball ball);

int collisionWithBar(Ball *ball, Bar bar, int onTop);

void collisionWithWindow(Ball *ball, Player *joueur1, Player *joueur2, int ballNumber);

int collisionWithBrick(Ball *ball, Brick *brick, Bar *bar1, Bar *bar2, Player *joueur1, Player *joueur2, Ball *ballSup);

#endif