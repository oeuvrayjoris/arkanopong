#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ball.h"
#include "bar.h"
#include "brick.h"
#include "geometry.h"

int collisionsBetweenBalls() {
	return 0;
}

int collisionBallBrick() {
	return 0;
}

int collisionBallBar(Ball ball, Bar bar) {
	return 0;
}

void affiche_tab(int *tab, int size) {
	int count;
	printf("{");
	for (count = 0; count < size; count++)
		printf("%d", tab[count]);
	printf("}\n");
}