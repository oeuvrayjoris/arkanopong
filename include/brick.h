#ifndef BRICK_H_
#define BRICK_H_

typedef struct Brick {
	float largeur;
	float longueur;
	int state;
	int type;
	GLuint texture;
	Point position;
} Brick;

typedef struct TableBrick {
	Brick *current;
	Brick *next;
} TableBrick;

Brick createBrick(float largeur, float longueur, int state, int type, GLuint texture, Point position);

#endif