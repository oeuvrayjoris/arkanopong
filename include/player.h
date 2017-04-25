#ifndef PLAYER_H_
#define PLAYER_H_

#include "player.h"

typedef struct Player {
	char *name;
	int score;
	int life;
	Color3D color;
} Player;


Player createPlayer(char *name, int score, int life, Color3D color);

void drawPlayer(Player player);

#endif