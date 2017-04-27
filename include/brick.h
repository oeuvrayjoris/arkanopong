#ifndef BRICK_H_
#define BRICK_H_

typedef struct Brick {
	float longueur_x;
	float longueur_y;
	int full;
	int state;
	Color3D color;
	Point position;
} Brick;

Brick createBrick(float longueur_x, float longueur_y, int full, int state, Color3D color, Point position);

void drawBrick(Brick brick);

#endif