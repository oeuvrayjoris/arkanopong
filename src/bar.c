#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "bar.h"

Bar createBar(float largeur, float longueur, int full, Color3D color, Point position) {
	Bar myBar;
	myBar.largeur = largeur;
	myBar.longueur = longueur;
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
			glVertex2f(-bar.largeur/2, bar.longueur/2);
			glVertex2f(bar.largeur/2, bar.longueur/2);
			glVertex2f(bar.largeur/2, -bar.longueur/2);
			glVertex2f(-bar.largeur/2, -bar.longueur/2);
		glEnd();
	glPopMatrix();

}