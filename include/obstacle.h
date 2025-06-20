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
    bool active;
} Obstacle;

typedef struct
{
    ObstacleType type;
    float spawnInterval;
    float timeSinceLastSpawn;
    float minDistance;
} ObstacleSpawner;

#define MAX_OBSTACLES 100
#define MAX_SPAWNERS 5

void InitSpawner(ObstacleSpawner *spawner, ObstacleType type, float interval, float minDist);
void TrySpawnObstacle(ObstacleSpawner *spawner, Obstacle *obstacles, int *obstacleCount, float delta, int playerPositionX);
void UpdateObstacles(Obstacle *obstacles, int obstacleCount, float delta);
void DrawObstacles(Obstacle *obstacles, int obstacleCount);

#endif
