#ifndef PLAYER_H_
#define PLAYER_H_

#include "player.h"

typedef struct Player {
	int life;
	Color3D color;
} Player;


Player createPlayer(int life, Color3D color);

void drawPlayer(Player player);

#endif