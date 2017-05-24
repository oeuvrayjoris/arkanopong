#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>

#include "images.h"

void image_coeur(int life1, int life2) {
	int i;
	GLuint texture;

	SDL_Surface *image = IMG_Load("images/coeur.png");
	if(image == NULL)
		printf("Erreur, l'image n'a pas pu être chargée\n");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(0, texture);

	GLenum format;
	switch(image->format->BytesPerPixel) {
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			return EXIT_FAILURE;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
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
	glTranslatef(0.7, -0.9, 0);
	for(i=0; i<life1; i++) {
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

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}