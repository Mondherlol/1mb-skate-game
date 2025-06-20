#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "raylib.h"

#define MAX_COLLECTIBLES 50

typedef struct
{
    Vector2 position;
    bool active;
} Collectible;

void InitCollectibles(Collectible *collectibles, int maxCollectibles);
void SpawnCollectible(Collectible *collectibles, int maxCollectibles);
void UpdateCollectibles(Collectible *collectibles, int maxCollectibles, float delta);
void DrawCollectibles(Collectible *collectibles, int maxCollectibles);

#endif