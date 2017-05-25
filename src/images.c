#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>

#include "geometry.h"
#include "images.h"
#include "ball.h"
#include "bar.h"
#include "brick.h"
#include "player.h"

void draw_coeur(GLuint texture, int life1, int life2) {
	int i;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    /* Dessin des coeurs */
    glPushMatrix();
	glTranslatef(-0.9, 0.9, 0);
    for(i=0; i<life2; i++) {
		glPushMatrix();
		glTranslatef(0.1*i, 0, 0);
	    glBegin(GL_QUADS);
	      glTexCoord2f(0, 0);
	      glVertex2f(-0.05, 0.05);
	      glTexCoord2f(1, 0);
	      glVertex2f(0.05, 0.05);
	      glTexCoord2f(1, 1);
	      glVertex2f(0.05, -0.05);
	      glTexCoord2f(0, 1);
	      glVertex2f(-0.05, -0.05);
	    glEnd();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -0.9, 0);
	for(i=0; i<life1; i++) {
		glPushMatrix();
		glTranslatef(-0.1*i, 0, 0);
	    glBegin(GL_QUADS);
	      glTexCoord2f(0, 0);
	      glVertex2f(-0.05, 0.05);
	      glTexCoord2f(1, 0);
	      glVertex2f(0.05, 0.05);
	      glTexCoord2f(1, 1);
	      glVertex2f(0.05, -0.05);
	      glTexCoord2f(0, 1);
	      glVertex2f(-0.05, -0.05);
	    glEnd();
		glPopMatrix();
	}
	glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void draw_brick(Brick brick) {
	if (brick.state > 0) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, brick.texture);

		glPushMatrix();
			glTranslatef(brick.position.x+brick.largeur/2, brick.position.y-brick.longueur/2, 0); // La brique sera placée par rapport à son coin gauche et non son centre pour plus de facilité
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex2f(-brick.largeur/2, brick.longueur/2);
				glTexCoord2f(1, 0);
				glVertex2f(brick.largeur/2, brick.longueur/2);
				glTexCoord2f(1, 1);
				glVertex2f(brick.largeur/2, -brick.longueur/2);
				glTexCoord2f(0, 1);
				glVertex2f(-brick.largeur/2, -brick.longueur/2);
			glEnd();
		glPopMatrix();

	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_TEXTURE_2D);
	    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	    glColor3ub(0,0,0);
	    glPushMatrix();
		glTranslatef(brick.position.x+brick.largeur/2, brick.position.y-brick.longueur/2, 0);
	    	glBegin(GL_LINE_LOOP);
				glVertex2f(-brick.largeur/2, brick.longueur/2);
				glVertex2f(brick.largeur/2, brick.longueur/2);
				glVertex2f(brick.largeur/2, -brick.longueur/2);
				glVertex2f(-brick.largeur/2, -brick.longueur/2);
			glEnd();
		glPopMatrix();
	}
}