#ifndef IMAGES_H_
#define IMAGES_H_

#include "brick.h"

void draw_coeur(GLuint texture, int life1, int life2);
void draw_brick(Brick brick);
void draw_menuprincipal(int statut, GLuint texture_arkanopong, GLuint texture_1player, GLuint texture_1playerhover, GLuint texture_2player, GLuint texture_2playerhover);

#endif