#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct
{
    Vector2 position;
    float velocityY;
    bool isJumping;
    int jumpBufferCounter;
    Rectangle frameRec;
    int currentFrame;
    int frameCounter;
    Vector2 offset; // Offset pour centrer le sprite

} Player;

Player InitPlayer();
void UpdatePlayer(Player *player);
void DrawPlayer(Texture2D spriteSheet, Player *player);

#endif
