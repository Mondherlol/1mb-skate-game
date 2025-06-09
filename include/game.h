#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "obstacle.h"
#include "raylib.h"

void CheckCollision(Player *player, Obstacle *obstacles, int obstacleCount);
void DrawGame(Texture2D spriteSheet, Player *player, Obstacle *obstacles, int obstacleCount);
void UpdateGame();
void InitGame();
#endif
