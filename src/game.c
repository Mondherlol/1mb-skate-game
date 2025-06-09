// game.c
#include "game.h"
#include "obstacle.h"
#include <math.h>

#define GROUND_Y 380
#define GROUND_HEIGHT 20

#define PLAYER_HITBOX_WIDTH 30
#define PLAYER_HITBOX_HEIGHT 50

Texture2D groundTexture;
float scrollX = 0.0f;
float scrollSpeed = 2.0f;

void InitGame()
{
    groundTexture = LoadTexture("../assets/route.jpg"); // Charge la texture du sol
}

void UpdateGame()
{
    scrollX -= scrollSpeed;
    if (scrollX <= -groundTexture.width)
    {
        scrollX = 0;
    }
}

void CheckCollision(Player *player, Obstacle *obstacles, int obstacleCount)
{
    float hitboxX = player->position.x + (50 - PLAYER_HITBOX_WIDTH) / 2;
    float hitboxY = player->position.y + (60 - PLAYER_HITBOX_HEIGHT);

    for (int i = 0; i < obstacleCount; i++)
    {
        if (!obstacles[i].active)
            continue;

        if (hitboxX < obstacles[i].position.x + 30 &&
            hitboxX + PLAYER_HITBOX_WIDTH > obstacles[i].position.x &&
            hitboxY < obstacles[i].position.y + 50 &&
            hitboxY + PLAYER_HITBOX_HEIGHT > obstacles[i].position.y)
        {
            player->position.x = 200;
            obstacles[i].active = false;
        }
    }
}

void DrawGame(Texture2D spriteSheet, Player *player, Obstacle *obstacles, int obstacleCount)
{
    // Route
    DrawRectangle(0, GROUND_Y, GetScreenWidth(), GROUND_HEIGHT, DARKGRAY);
    // Taille de la fenêtre
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Taille redimensionnée pour que l’image couvre tout l’écran
    Rectangle dest = {0, 0, screenWidth, screenHeight};

    // Affichage en 2 morceaux côte à côte pour créer la boucle
    Rectangle source1 = {fmodf(scrollX, groundTexture.width), 0, groundTexture.width - fmodf(scrollX, groundTexture.width), groundTexture.height};
    Rectangle dest1 = {0, 0, (screenWidth * source1.width) / groundTexture.width, screenHeight};

    Rectangle source2 = {0, 0, fmodf(scrollX, groundTexture.width), groundTexture.height};
    Rectangle dest2 = {dest1.width, 0, screenWidth - dest1.width, screenHeight};

    // Dessiner les deux parties
    DrawTexturePro(groundTexture, source1, dest1, (Vector2){0, 0}, 0.0f, WHITE);
    DrawTexturePro(groundTexture, source2, dest2, (Vector2){0, 0}, 0.0f, WHITE);

    DrawText("Skate et évite les obstacles !", 10, 10, 20, DARKGRAY);
    DrawPlayer(spriteSheet, player);
    DrawObstacles(obstacles, obstacleCount);
}