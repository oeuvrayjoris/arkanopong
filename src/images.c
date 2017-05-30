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

void draw_menuprincipal(int statut, GLuint texture_arkanopong, GLuint texture_1player, GLuint texture_1playerhover, GLuint texture_2player, GLuint texture_2playerhover, GLuint texture_dev, GLuint texture_infos) {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // ARKANOPONG
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_arkanopong);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.5, 0.1);
      glTexCoord2f(1, 0);
      glVertex2f(0.5, 0.1);
      glTexCoord2f(1, 1);
      glVertex2f(0.5, -0.1);
      glTexCoord2f(0, 1);
      glVertex2f(-0.5, -0.1);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// INFOS
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_infos);
	glPushMatrix();
	glTranslatef(0, 0.3, 0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.3, 0.05);
      glTexCoord2f(1, 0);
      glVertex2f(0.3, 0.05);
      glTexCoord2f(1, 1);
      glVertex2f(0.3, -0.05);
      glTexCoord2f(0, 1);
      glVertex2f(-0.3, -0.05);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// DEVELOPPE PAR
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_dev);
	glPushMatrix();
	glTranslatef(0, -0.8, 0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.45, 0.03);
      glTexCoord2f(1, 0);
      glVertex2f(0.45, 0.03);
      glTexCoord2f(1, 1);
      glVertex2f(0.45, -0.03);
      glTexCoord2f(0, 1);
      glVertex2f(-0.45, -0.03);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// 1 JOUEUR
	glEnable(GL_TEXTURE_2D);
    if(statut == 0 || statut == 2)
    	glBindTexture(GL_TEXTURE_2D, texture_1player);
    else if(statut == 1)
    	glBindTexture(GL_TEXTURE_2D, texture_1playerhover);
	glPushMatrix();
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.3, 0.05);
      glTexCoord2f(1, 0);
      glVertex2f(0.3, 0.05);
      glTexCoord2f(1, 1);
      glVertex2f(0.3, -0.05);
      glTexCoord2f(0, 1);
      glVertex2f(-0.3, -0.05);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// 2 JOUEURS
	glEnable(GL_TEXTURE_2D);
	if(statut == 0 || statut == 1)
    	glBindTexture(GL_TEXTURE_2D, texture_2player);
    else if(statut == 2)
    	glBindTexture(GL_TEXTURE_2D, texture_2playerhover);

	glPushMatrix();
	glTranslatef(0, -0.2, 0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.3, 0.05);
      glTexCoord2f(1, 0);
      glVertex2f(0.3, 0.05);
      glTexCoord2f(1, 1);
      glVertex2f(0.3, -0.05);
      glTexCoord2f(0, 1);
      glVertex2f(-0.3, -0.05);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void draw_results(int statut, GLuint texture_jwon, GLuint texture_menu, GLuint texture_menuhover, GLuint texture_rejouer, GLuint texture_rejouerhover) {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // JWON
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_jwon);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.5, 0.2);
      glTexCoord2f(1, 0);
      glVertex2f(0.5, 0.2);
      glTexCoord2f(1, 1);
      glVertex2f(0.5, -0.2);
      glTexCoord2f(0, 1);
      glVertex2f(-0.5, -0.2);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// REJOUER
	glEnable(GL_TEXTURE_2D);
    if(statut == -1 || statut == 0)
    	glBindTexture(GL_TEXTURE_2D, texture_rejouer);
    else if(statut == 1 || statut == 2)
    	glBindTexture(GL_TEXTURE_2D, texture_rejouerhover);
	glPushMatrix();
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.3, 0.05);
      glTexCoord2f(1, 0);
      glVertex2f(0.3, 0.05);
      glTexCoord2f(1, 1);
      glVertex2f(0.3, -0.05);
      glTexCoord2f(0, 1);
      glVertex2f(-0.3, -0.05);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// MENU
	glEnable(GL_TEXTURE_2D);
	if(statut == -1 || statut == 1 || statut == 2)
    	glBindTexture(GL_TEXTURE_2D, texture_menu);
    else if(statut == 0)
    	glBindTexture(GL_TEXTURE_2D, texture_menuhover);

	glPushMatrix();
	glTranslatef(0, -0.2, 0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex2f(-0.3, 0.05);
      glTexCoord2f(1, 0);
      glVertex2f(0.3, 0.05);
      glTexCoord2f(1, 1);
      glVertex2f(0.3, -0.05);
      glTexCoord2f(0, 1);
      glVertex2f(-0.3, -0.05);
    glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}