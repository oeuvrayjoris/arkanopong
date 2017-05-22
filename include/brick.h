#ifndef BRICK_H_
#define BRICK_H_

typedef struct Brick {
	float largeur;
	float longueur;
	int full;
	int state;
	int type;
	Color3D color;
	Point position;
} Brick;

typedef struct TableBrick {
	Brick *current;
	Brick *next;
} TableBrick;

Brick createBrick(float largeur, float longueur, int full, int state, int type, Color3D color, Point position);

void drawBrick(Brick brick);

#endif