#include "raylib.h"
#include "player.h"
#include "obstacle.h"
#include "game.h"
#include "collectible.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define MAX_COLLECTIBLES 50

static Collectible collectibles[MAX_COLLECTIBLES];
static int score = 0;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Skate Runner - 1MB Challenge");
    SetTargetFPS(60);

    // Charger les textures et initialiser le joueur
    Texture2D spriteSheet = LoadTexture("../assets/Conan_Sprite_Skate.png");
    Player player = InitPlayer();

    // Initialisation des obstacles
    Obstacle obstacles[MAX_OBSTACLES];
    int obstacleCount = 5;

    // Initialisation des spawners
    ObstacleSpawner spawners[MAX_SPAWNERS];
    int spawnerCount = 2;

    InitSpawner(&spawners[0], OBSTACLE_TYPE_SIDE, 2.0f, 150.0f);    // obstacle qui arrive de droite
    InitSpawner(&spawners[1], OBSTACLE_TYPE_FALLING, 3.5f, 200.0f); // obstacle qui tombe du ciel

    InitGame(); // Initialisation du jeu
    InitCollectibles(collectibles, MAX_COLLECTIBLES);

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime(); // delta time pour fluidité

        UpdateGame(&player);
        UpdatePlayer(&player);

        for (int i = 0; i < spawnerCount; i++)
        {
            TrySpawnObstacle(&spawners[i], obstacles, &obstacleCount, delta, (int)player.position.x);
        }

        UpdateObstacles(obstacles, obstacleCount, delta);
        CheckCollision(&player, obstacles, obstacleCount);
        CheckCollectibleCollision(&player, MAX_COLLECTIBLES);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGame(spriteSheet, &player, obstacles, obstacleCount);
        EndDrawing();
    }

    UnloadTexture(spriteSheet);
    CloseWindow();
    return 0;
}
