#include "obstacle.h"
#include <math.h>
void InitSpawner(ObstacleSpawner *spawner, ObstacleType type, float interval, float minDist)
{
    spawner->type = type;
    spawner->spawnInterval = interval;
    spawner->timeSinceLastSpawn = 0.0f;
    spawner->minDistance = minDist;
}

void TrySpawnObstacle(ObstacleSpawner *spawner, Obstacle *obstacles, int *obstacleCount, float delta, int playerPositionX)
{
    spawner->timeSinceLastSpawn += delta;

    if (spawner->timeSinceLastSpawn >= spawner->spawnInterval)
    {
        bool canSpawn = true;
        for (int i = 0; i < *obstacleCount; i++)
        {
            if (obstacles[i].active &&
                fabsf(obstacles[i].position.x - 800) < spawner->minDistance)
            {
                canSpawn = false;
                break;
            }
        }

        if (canSpawn && *obstacleCount < MAX_OBSTACLES)
        {
            Obstacle obs = {0};
            obs.type = spawner->type;
            obs.active = true;

            if (obs.type == OBSTACLE_TYPE_SIDE)
            {
                obs.position = (Vector2){800, 380 - 50};
                obs.velocity = (Vector2){-200, 0};
            }
            else if (obs.type == OBSTACLE_TYPE_FALLING)
            {
                obs.position = (Vector2){GetRandomValue(playerPositionX - 150, playerPositionX + 150), -50};
                obs.velocity = (Vector2){0, 250};
            }

            obstacles[(*obstacleCount)++] = obs;
            spawner->timeSinceLastSpawn = 0.0f;
        }
    }
}

void UpdateObstacles(Obstacle *obstacles, int obstacleCount, float delta)
{
    for (int i = 0; i < obstacleCount; i++)
    {
        if (!obstacles[i].active)
            continue;

        obstacles[i].position.x += obstacles[i].velocity.x * delta;
        obstacles[i].position.y += obstacles[i].velocity.y * delta;

        if (obstacles[i].position.x < -50 || obstacles[i].position.y > GetScreenHeight())
        {
            obstacles[i].active = false;
        }
    }
}

void DrawObstacles(Obstacle *obstacles, int obstacleCount)
{
    for (int i = 0; i < obstacleCount; i++)
    {
        if (!obstacles[i].active)
            continue;
        DrawRectangle(obstacles[i].position.x, obstacles[i].position.y, 30, 50, BLACK);
    }
}
