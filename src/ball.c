#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "ball.h"
#include "bar.h"
#include "brick.h"

Ball createBall(float radius, int full, Color3D color, Point position, Vector vector) {
	Ball ball;
	ball.radius = radius;
	ball.full = full;
	ball.color = color;
	ball.position = position;
	ball.vector = vector;
	return ball;
}

void drawBall(Ball ball) {
	glColor3ub(ball.color.red, ball.color.green, ball.color.blue);
	glPushMatrix();
	
	glTranslatef(ball.position.x, ball.position.y, 0);

	glBegin(ball.full ? GL_POLYGON : GL_LINE_LOOP);
		float j;
		for(j=0; j<2*M_PI; j+=0.01) {
			glVertex2f(cos(j)*ball.radius, sin(j)*ball.radius);
		}
	glEnd();

	glPopMatrix();
}

// Cette fonction vérifie s'il y a collision entre une des balles et une des barres et modifie le vecteur directeur s'il y a collision
int collisionWithBar(Ball *ball, Bar bar, int onTop) {
	if (onTop) {
		/* Collision avec la barre 1 */
		if(ball->position.y-ball->radius <= (bar.position.y + bar.longueur/2)) {
			/* Balle au centre */
			if(ball->position.x <= (bar.position.x + bar.largeur/4) && ball->position.x >= (bar.position.x - bar.largeur/4)) {
				ball->vector.y *= -1;
				return 1;
			}
			/* Balle à droite */
			else if(ball->position.x <= (bar.position.x + bar.largeur/2) && ball->position.x > (bar.position.x + bar.largeur/4)) { // Balle à droite de la barre
				ball->vector.x = 0.01;
				ball->vector.y *= -1;
				return 1;
			}
			/* Balle à gauche */
			else if(ball->position.x < (bar.position.x - bar.largeur/4) && ball->position.x >= (bar.position.x - bar.largeur/2)) { // Balle à gauche de la barre
				ball->vector.x = -0.01;
				ball->vector.y *= -1;
				return 1;
			}
		}
		return 0;
	}
	else {
	/* Collision avec la barre 2 */
		if(ball->position.y+ball->radius >= (bar.position.y - bar.longueur/2)) {
			/* Balle au centre */
			if(ball->position.x >= (bar.position.x - bar.largeur/4) && ball->position.x <= (bar.position.x + bar.largeur/4)) {
				ball->vector.y *= -1;
				return 1;
			}
			/* Balle à droite */
			else if(ball->position.x >= (bar.position.x - bar.largeur/2) && ball->position.x < (bar.position.x - bar.largeur/4)) { // Balle à droite de la barre
				ball->vector.x = -0.01;
				ball->vector.y *= -1;
				return 1;
			}
			/* Balle à gauche */
			else if(ball->position.x > (bar.position.x + bar.largeur/4) && ball->position.x <= (bar.position.x + bar.largeur/2)) { // Balle à gauche de la barre
				ball->vector.x = 0.01;
				ball->vector.y *= -1;
				return 1;
			}
		}
		return 0;
	}
}

// Cette fonction vérifie s'il y a collision avec la fenêtre (ou sortie de jeu)
int collisionWithWindow(Ball ball) {
	return 0;
}

int collisionWithBrick(Brick *brick, Ball *ball) {
	/*if (brick->state) {

		// gestion
		switch
	}*/
	return 0;
}