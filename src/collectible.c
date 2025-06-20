#include "collectible.h"
#include <stdlib.h>

void InitCollectibles(Collectible *collectibles, int maxCollectibles)
{
    for (int i = 0; i < maxCollectibles; i++)
    {
        collectibles[i].active = false;
    }
}

void SpawnCollectible(Collectible *collectibles, int maxCollectibles)
{
    for (int i = 0; i < maxCollectibles; i++)
    {
        if (!collectibles[i].active)
        {
            collectibles[i].position = (Vector2){800, GetRandomValue(200, 350)}; // Apparait à droite, au sol
            collectibles[i].active = true;
            break;
        }
    }
}

void UpdateCollectibles(Collectible *collectibles, int maxCollectibles, float delta)
{
    for (int i = 0; i < maxCollectibles; i++)
    {
        if (!collectibles[i].active)
            continue;
        collectibles[i].position.x -= 200 * delta; // Vitesse de défilement
        if (collectibles[i].position.x < -20)
        {
            collectibles[i].active = false;
        }
    }
}

void DrawCollectibles(Collectible *collectibles, int maxCollectibles)
{
    for (int i = 0; i < maxCollectibles; i++)
    {
        if (!collectibles[i].active)
            continue;
        DrawCircleV(collectibles[i].position, 10, GOLD);
    }
}