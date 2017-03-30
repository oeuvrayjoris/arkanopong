#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "ball.h"

Ball createBall(float radius, int full, Color3D color, Point position, Vector vector) {
	Ball myBall;
	myBall.radius = radius;
	myBall.full = full;
	myBall.color = color;
	myBall.position = position;
	myBall.vector = vector;
	return myBall;
}

void drawBall(Ball ball) {
	glColor3ub(ball.color.red, ball.color.green, ball.color.blue);
	glPushMatrix();
		glTranslatef(ball.position.x, ball.position.y, 0);
	glPopMatrix();

	glBegin(ball.full ? GL_POLYGON : GL_LINE_LOOP);
		float j;
		for(j=0; j<2*M_PI; j+=0.01) {
			glTexCoord2f(cos(j)+ball.radius, sin(j)+ball.radius);
			glVertex2f(cos(j), sin(j));
		}
	glEnd();
}