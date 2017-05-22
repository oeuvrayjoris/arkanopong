#ifndef BAR_H_
#define BAR_H_

typedef struct Bar {
	float largeur;
	float longueur;
	int full;
	Color3D color;
	Point position;
} Bar;

Bar createBar(float largeur, float longueur, int full, Color3D color, Point position);

void drawBar(Bar bar);

#endif