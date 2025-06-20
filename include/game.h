#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "obstacle.h"
#include "raylib.h"
#include "collectible.h"

void CheckCollision(Player *player, Obstacle *obstacles, int obstacleCount);
void DrawGame(Texture2D spriteSheet, Player *player, Obstacle *obstacles, int obstacleCount);
void UpdateGame(Player *player);
void InitGame();
void CheckCollectibleCollision(Player *player, int maxCollectibles);
#endif
