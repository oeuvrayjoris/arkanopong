#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "drawing.h"

/** Fonctions de dessin canonique. **/

/**
 * Crée un carré
 * int full : booléen devenant 0 (vide), 1 (plein)
*/
void draw_square(int full) {
  /** Dessine un carré (plein ou non) de côté 1 et centré en (0, 0). **/
  glColor3f(0,0,0);
  glBegin(full ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, -0.5);
  glEnd();
}

/**
 * Crée un cercle
 * int full : booléen devenant 0 (vide), 1 (plein)
 */
void draw_circle(int full) {
  glBegin(full ? GL_POLYGON : GL_LINE_LOOP);
  float j;
  for(j=0; j<2*M_PI; j+=0.01) {
    glTexCoord2f(cos(j)+0.5, sin(j)+0.5);
    glVertex2f(cos(j), sin(j));
  }
  glEnd();
}

void draw_rounded_square(int full, float radius) {
  /** Dessine un carré (plein ou non) de côté 1 et centré en (0, 0), dont les bords sont arrondis de rayon = radius. **/
  glBegin(full ? GL_POLYGON : GL_LINES);
    glVertex2f(-0.5+radius, 0.5);
    glVertex2f(0.5-radius, 0.5);
    glVertex2f(0.5, 0.5-radius);
    glVertex2f(0.5, -0.5+radius);
    glVertex2f(0.5-radius, -0.5);
    glVertex2f(-0.5+radius, -0.5);
    glVertex2f(-0.5, -0.5+radius);
    glVertex2f(-0.5, 0.5-radius);
  glEnd();

  float j;

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=M_PI/2; j<M_PI; j+=0.01)
    glVertex2f(-0.5+radius+cos(j)*radius, 0.5-radius+sin(j)*radius);
  glEnd();

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=0; j<M_PI/2; j+=0.01)
    glVertex2f(0.5-radius+cos(j)*radius, 0.5-radius+sin(j)*radius);
  glEnd();

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=3*M_PI/2; j<2*M_PI; j+=0.01)
    glVertex2f(0.5-radius+cos(j)*radius, -0.5+radius+sin(j)*radius);
  glEnd();

  glBegin(full ? GL_POLYGON : GL_LINE_STRIP);
  for(j=M_PI; j<3*M_PI/2; j+=0.01)
    glVertex2f(-0.5+radius+cos(j)*radius, -0.5+radius+sin(j)*radius);
  glEnd();
}
