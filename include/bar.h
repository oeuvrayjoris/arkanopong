#ifndef BAR_H_
#define BAR_H_

typedef struct Bar {
	float longueur_x;
	float longueur_y;
	int full;
	Color3D color;
	Point position;
} Bar;

Bar createBar(float longueur_x, float longueur_y, int full, Color3D color, Point position);

void drawBar(Bar bar);

#endif