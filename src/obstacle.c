#include "obstacle.h"
#include <math.h>

#define FRAME_SPEED 10
#define MAX_FRAMES 4

void InitSpawner(ObstacleSpawner *spawner, ObstacleType type, float interval, float minDist)
{
    spawner->type = type;
    spawner->spawnInterval = interval;
    spawner->timeSinceLastSpawn = 0.0f;
    spawner->minDistance = minDist;
    spawner->spritesheet = LoadTexture("../assets/VOITURE.png");
}

void unloadSpawner(ObstacleSpawner *spawner)
{
    UnloadTexture(spawner->spritesheet);
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
                obs.velocity = (Vector2){-200, 0};
                obs.frameRec = (Rectangle){0, 0, 200, 100}; // Adjust frame rectangle as needed
                obs.currentFrame = 0;
                obs.frameCounter = 0;
                obs.offset = (Vector2){0, 0};           // Offset to center the sprite
                obs.spritesheet = spawner->spritesheet; // Use the spawner's spritesheet
                obs.width = 200;                        // Width of the obstacle
                obs.height = 100;                       // Height of the obstacle
                obs.scale = 1.50f;                      // Scale factor for the obstacle

                obs.position = (Vector2){800, 380 - obs.height * obs.scale + 10 * obs.scale}; // Position the obstacle at the right edge of the screen
            }
            else if (obs.type == OBSTACLE_TYPE_FALLING)
            {
                obs.position = (Vector2){GetRandomValue(playerPositionX - 150, playerPositionX + 150), -50};
                obs.velocity = (Vector2){0, 250};
                obs.width = 30;   // Width of the falling obstacle
                obs.height = 50;  // Height of the falling obstacle
                obs.scale = 1.0f; // Scale factor for the falling obstacle
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

        if (obstacles[i].type == OBSTACLE_TYPE_SIDE)
        {
            // Calculate scaled dimensions
            float scaledWidth = obstacles[i].frameRec.width * obstacles[i].scale;
            float scaledHeight = obstacles[i].frameRec.height * obstacles[i].scale;

            Rectangle destRec = {
                obstacles[i].position.x + obstacles[i].offset.x,
                obstacles[i].position.y + obstacles[i].offset.y,
                scaledWidth,
                scaledHeight};

            DrawTexturePro(obstacles[i].spritesheet,
                           obstacles[i].frameRec,
                           destRec,
                           (Vector2){0, 0},
                           0.0f,
                           WHITE);

            // Update frame for animation
            if (++obstacles[i].frameCounter >= FRAME_SPEED)
            {
                obstacles[i].frameCounter = 0;
                obstacles[i].currentFrame = (obstacles[i].currentFrame + 1) % MAX_FRAMES;
                obstacles[i].frameRec.x = obstacles[i].currentFrame * obstacles[i].frameRec.width;
            }
        }
        else
            DrawRectangle(obstacles[i].position.x, obstacles[i].position.y, 30, 50, BLACK);
    }
}
