#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "brick.h"


Brick createBrick(float largeur, float longueur, int state, int type, GLuint texture, Point position) {
	Brick myBrick;
	myBrick.largeur = largeur;
	myBrick.longueur = longueur;
	myBrick.state = 1;
	myBrick.type = type;
	myBrick.texture = texture;
	myBrick.position = position;
	return myBrick;
}