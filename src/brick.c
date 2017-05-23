#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "brick.h"


Brick createBrick(float largeur, float longueur, int full, int state, int type, Color3D color, Point position) {
	Brick myBrick;
	myBrick.largeur = largeur;
	myBrick.longueur = longueur;
	myBrick.full = full;
	myBrick.state = 1;
	myBrick.type;
	myBrick.color = color;
	myBrick.position = position;
	return myBrick;
}

void drawBrick(Brick brick) {
	if (brick.state > 0) {
		glColor3ub(brick.color.red, brick.color.green, brick.color.blue);
		glPushMatrix();
			glTranslatef(brick.position.x+brick.largeur/2, brick.position.y-brick.longueur/2, 0); // La brique sera placée par rapport à son coin gauche et non son centre pour plus de facilité
			glBegin(brick.full ? GL_QUADS : GL_LINE_LOOP);
				glVertex2f(-brick.largeur/2, brick.longueur/2);
				glVertex2f(brick.largeur/2, brick.longueur/2);
				glVertex2f(brick.largeur/2, -brick.longueur/2);
				glVertex2f(-brick.largeur/2, -brick.longueur/2);
			glEnd();
		glPopMatrix();
	}
}