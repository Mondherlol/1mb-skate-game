#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

typedef enum
{
    OBSTACLE_TYPE_SIDE,
    OBSTACLE_TYPE_FALLING
} ObstacleType;

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    ObstacleType type;
    Rectangle frameRec;
    int currentFrame;
    int frameCounter;
    Vector2 offset; // Offset pour centrer le sprite
    bool active;
    Texture2D spritesheet; // Texture pour les obstacles
    int width;
    int height;
    float scale; // Facteur d'échelle pour l'obstacle
} Obstacle;

typedef struct
{
    ObstacleType type;
    float spawnInterval;
    float timeSinceLastSpawn;
    float minDistance;
    Texture2D spritesheet; // Texture pour les obstacles de type OBSTACLE_TYPE_SIDE
} ObstacleSpawner;

#define MAX_OBSTACLES 100
#define MAX_SPAWNERS 5

void InitSpawner(ObstacleSpawner *spawner, ObstacleType type, float interval, float minDist);
void TrySpawnObstacle(ObstacleSpawner *spawner, Obstacle *obstacles, int *obstacleCount, float delta, int playerPositionX);
void UpdateObstacles(Obstacle *obstacles, int obstacleCount, float delta);
void DrawObstacles(Obstacle *obstacles, int obstacleCount);
void unloadSpawner(ObstacleSpawner *spawner);

#endif
