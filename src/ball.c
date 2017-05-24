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

// Cette fonction vérifie s'il y a collision avec une brique
int collisionWithBrick(Ball *ball, Brick *brick, Bar *bar1, Bar *bar2) {
	// Si la brique est encore "active" (non détruite)
	if (brick->state > 0) {
		int collision = 0;

		// Top
		if((ball->position.y-ball->radius) - brick->position.y >= -0.01 && (ball->position.y-ball->radius) - brick->position.y <= 0.01) {
			/* Balle au centre */
			if(ball->position.x == brick->position.x + brick->largeur/2) {
				ball->vector.y *= -1;
				collision = 1;
			}
			/* Balle à droite */
			else if(ball->position.x > (brick->position.x + brick->largeur/2) && ball->position.x <= (brick->position.x + brick->largeur)) { // Balle à droite de la barre
				ball->vector.x = 0.01;
				ball->vector.y *= -1;
				collision = 1;
			}
			/* Balle à gauche */
			else if(ball->position.x < (brick->position.x + brick->largeur/2) && ball->position.x >= (brick->position.x)) { // Balle à gauche de la barre
				ball->vector.x = -0.01;
				ball->vector.y *= -1;
				collision = 1;
			}
		}

		// Bottom
		if((ball->position.y+ball->radius) - (brick->position.y-brick->longueur) >= -0.01 && (ball->position.y+ball->radius) - (brick->position.y-brick->longueur) <= 0.01) {
			/* Balle au centre */
			if(ball->position.x == brick->position.x + brick->largeur/2) {
				ball->vector.y *= -1;
				collision = 1;
			}
			/* Balle à droite */
			else if(ball->position.x > (brick->position.x + brick->largeur/2) && ball->position.x <= (brick->position.x + brick->largeur)) { // Balle à droite de la barre
				ball->vector.x = 0.01;
				ball->vector.y *= -1;
				collision = 1;
			}
			/* Balle à gauche */
			else if(ball->position.x < (brick->position.x + brick->largeur/2) && ball->position.x >= (brick->position.x)) { // Balle à gauche de la barre
				ball->vector.x = -0.01;
				ball->vector.y *= -1;
				collision = 1;
			}
		}

		// Left
		if ((ball->position.x+ball->radius) - (brick->position.x) >= -0.01 && (ball->position.x+ball->radius) - (brick->position.x) <= 0.01) {
			/* Balle en haut */
			if (ball->position.y >= brick->position.y && ball->position.y <= brick->position.y - (brick->longueur/2)) {
				ball->vector.x = -0.01;
				ball->vector.y *= -1;
				collision = 1;
			}
			/* Balle en bas */
			else if (ball->position.y > brick->position.y - (brick->longueur/2) && ball->position.y <= brick->position.y - brick->longueur) {
				ball->vector.x = -0.01;
				ball->vector.y *= 1;
				collision = 1;
			}
		}

		// Right
		if ((ball->position.x-ball->radius) - (brick->position.x+brick->largeur) >= -0.01 && (ball->position.x-ball->radius) - (brick->position.x+brick->largeur) <= 0.01) {
			/* Balle en haut */
			if (ball->position.y >= brick->position.y && ball->position.y <= brick->position.y - (brick->longueur/2)) {
				ball->vector.x = 0.01;
				ball->vector.y *= -1;
				collision = 1;
			}
			/* Balle en bas */
			else if (ball->position.y > brick->position.y - (brick->longueur/2) && ball->position.y <= brick->position.y - brick->longueur) {
				ball->vector.x = 0.01;
				ball->vector.y *= 1;
				collision = 1;
			}
		}

		if (collision) {
			// Gestion de la brique en fonction de son type
			switch (brick->type) {
				case 0: // Normal
					brick->state = 0;
					break;
				case 1: // Indestructible
					brick->state = 1;
					break;
				case 2: // Bonus 1 : agrandissement de la barre
					if(ball->vector.y < 0) { // joueur1
						bar1->largeur += 0.2;
					}
					else {
						bar2->largeur += 0.2;
					}
					brick->state = 0;
					break;
				case 3: // Bonus 2
					brick->state = 0;
					break;
				case 4: // Bonus 3
					brick->state = 0;
					break;
				case 5: // Bonus 4
					brick->state = 0;
					break;
				case 6: // Malus
					brick->state = 0;
					break;
				default:
					break;
			}
		}
	}
	return 0;
}