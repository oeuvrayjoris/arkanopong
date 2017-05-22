#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "brick.h"


Brick createBrick(float largeur, float longueur, int full, int state, Color3D color, Point position) {
	Brick myBrick;
	myBrick.largeur = largeur;
	myBrick.longueur = longueur;
	myBrick.full = full;
	myBrick.state = 1;
	myBrick.type = 1;
	myBrick.color = color;
	myBrick.position = position;
	return myBrick;
}

void drawBrick(Brick brick) {
	if (brick.state != 1) {
		glColor3ub(brick.color.red, brick.color.green, brick.color.blue);
		glPushMatrix();
			glTranslatef(brick.position.x+brick.largeur/2, brick.position.y-brick.longueur/2, 0);
			glBegin(brick.full ? GL_QUADS : GL_LINE_LOOP);
				glVertex2f(-brick.largeur/2, brick.longueur/2);
				glVertex2f(brick.largeur/2, brick.longueur/2);
				glVertex2f(brick.largeur/2, -brick.longueur/2);
				glVertex2f(-brick.largeur/2, -brick.longueur/2);
			glEnd();
		glPopMatrix();
	}
}