#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "player.h"

Player createPlayer(char *name, int score, int life, Color3D color) {
	Player myPlayer;
	myPlayer.name = name;
	myPlayer.score = score;
	myPlayer.life = life;
	myPlayer.color = color;
	return myPlayer;
}

void drawPlayer(Player player) {
	glColor3ub(player.color.red, player.color.green, player.color.blue);
}