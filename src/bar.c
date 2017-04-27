#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "bar.h"

Bar createBar(float longueur_x, float longueur_y, int full, Color3D color, Point position) {
	Bar myBar;
	myBar.longueur_x = longueur_x;
	myBar.longueur_y = longueur_y;
	myBar.full = full;
	myBar.color = color;
	myBar.position = position;
	return myBar;
}

void drawBar(Bar bar) {

	glColor3ub(bar.color.red, bar.color.green, bar.color.blue);
	glPushMatrix();
		glTranslatef(bar.position.x, bar.position.y, 0);
		glBegin(bar.full ? GL_QUADS : GL_LINE_LOOP);
			glVertex2f(-bar.longueur_x/2, bar.longueur_y/2);
			glVertex2f(bar.longueur_x/2, bar.longueur_y/2);
			glVertex2f(bar.longueur_x/2, -bar.longueur_y/2);
			glVertex2f(-bar.longueur_x/2, -bar.longueur_y/2);
		glEnd();
	glPopMatrix();

}