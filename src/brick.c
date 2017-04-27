#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "brick.h"


Brick createBrick(float longueur_x, float longueur_y, int full, int state, Color3D color, Point position) {
	Brick myBrick;
	myBrick.longueur_x = longueur_x;
	myBrick.longueur_y = longueur_y;
	myBrick.full = full;
	myBrick.state = 1;
	myBrick.color = color;
	myBrick.position = position;
	return myBrick;
}

void drawBrick(Brick brick) {
	glColor3ub(brick.color.red, brick.color.green, brick.color.blue);
	glPushMatrix();
		glTranslatef(brick.position.x, brick.position.y, 0);
		glBegin(brick.full ? GL_QUADS : GL_LINE_LOOP);
			glVertex2f(-brick.longueur_x/2, brick.longueur_y/2);
			glVertex2f(brick.longueur_x/2, brick.longueur_y/2);
			glVertex2f(brick.longueur_x/2, -brick.longueur_y/2);
			glVertex2f(-brick.longueur_x/2, -brick.longueur_y/2);
		glEnd();
	glPopMatrix();
}