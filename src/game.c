// game.c
#include "game.h"
#include "obstacle.h"
#include "collectible.h"
#include <math.h>
#include <stdio.h>

#define GROUND_Y 380
#define GROUND_HEIGHT 20

#define PLAYER_HITBOX_WIDTH 30
#define PLAYER_HITBOX_HEIGHT 60

Texture2D groundTexture;
float scrollX = 0.0f;
float scrollSpeed = 2.0f;

// Variables globales pour le score et le timer
static int score = 0;
static float survivalTime = 0.0f;

#define MAX_COLLECTIBLES 50
static Collectible collectibles[MAX_COLLECTIBLES];
static float collectibleSpawnTimer = 0.0f;

void InitGame()
{
    groundTexture = LoadTexture("../assets/route.jpg"); // Charge la texture du sol
    InitCollectibles(collectibles, MAX_COLLECTIBLES);
    score = 0;
    survivalTime = 0.0f;
}

void UpdateGame(Player *player)
{
    scrollX -= scrollSpeed;
    if (scrollX <= -groundTexture.width)
    {
        scrollX = 0;
    }
    // Timer de survie
    survivalTime += GetFrameTime();
    // Apparition des collectibles
    collectibleSpawnTimer += GetFrameTime();
    if (collectibleSpawnTimer > 1.5f)
    { // toutes les 1.5 secondes
        SpawnCollectible(collectibles, MAX_COLLECTIBLES);
        collectibleSpawnTimer = 0.0f;
    }
    UpdateCollectibles(collectibles, MAX_COLLECTIBLES, GetFrameTime());
}
void CheckCollision(Player *player, Obstacle *obstacles, int obstacleCount)
{
    float hitboxX = player->position.x + 25 - (PLAYER_HITBOX_WIDTH / 2);
    float hitboxY = player->position.y - (PLAYER_HITBOX_HEIGHT / 2);

    DrawRectangleLines(hitboxX, hitboxY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, RED);

    for (int i = 0; i < obstacleCount; i++)
    {
        if (!obstacles[i].active)
            continue;

        if (hitboxX < obstacles[i].position.x + 30 &&
            hitboxX + PLAYER_HITBOX_WIDTH > obstacles[i].position.x &&
            hitboxY < obstacles[i].position.y + 30 &&
            hitboxY + PLAYER_HITBOX_HEIGHT > obstacles[i].position.y)
        {
            player->position.x = 200;
            obstacles[i].active = false;
        }
    }
}

void CheckCollectibleCollision(Player *player, int maxCollectibles)
{
    for (int i = 0; i < MAX_COLLECTIBLES; i++)
    {
        DrawCircleLines(collectibles[i].position.x, collectibles[i].position.y, 30, RED);
        float hitboxX = player->position.x + (PLAYER_HITBOX_WIDTH) / 2;
        float hitboxY = player->position.y + (PLAYER_HITBOX_HEIGHT);

        if (
            collectibles[i].active &&
            hitboxX < collectibles[i].position.x + 30 &&
            hitboxX + PLAYER_HITBOX_WIDTH > collectibles[i].position.x &&
            hitboxY < collectibles[i].position.y + 50 &&
            hitboxY + PLAYER_HITBOX_HEIGHT > collectibles[i].position.y)
        {
            printf("Collectible touché !\n");
            collectibles[i].active = false;
            player->collectibles++;
            score += 10; // Augmente le score de 10 points
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

    // Taille redimensionnée pour que l'image couvre tout l'écran
    Rectangle dest = {0, 0, screenWidth, screenHeight};

    // Affichage en 2 morceaux côte à côte pour créer la boucle
    Rectangle source1 = {fmodf(scrollX, groundTexture.width), 0, groundTexture.width - fmodf(scrollX, groundTexture.width), groundTexture.height};
    Rectangle dest1 = {0, 0, (screenWidth * source1.width) / groundTexture.width, screenHeight};

    Rectangle source2 = {0, 0, fmodf(scrollX, groundTexture.width), groundTexture.height};
    Rectangle dest2 = {dest1.width, 0, screenWidth - dest1.width, screenHeight};

    // // Dessiner les deux parties
    // DrawTexturePro(groundTexture, source1, dest1, (Vector2){0, 0}, 0.0f, WHITE);
    // DrawTexturePro(groundTexture, source2, dest2, (Vector2){0, 0}, 0.0f, WHITE);

    DrawText("Skate et évite les obstacles !", 10, 10, 20, DARKGRAY);
    DrawPlayer(spriteSheet, player);
    DrawObstacles(obstacles, obstacleCount);
    DrawCollectibles(collectibles, MAX_COLLECTIBLES);
    // Affichage du score en haut à droite
    char scoreText[32];
    sprintf(scoreText, "Score : %d", score);
    int scoreWidth = MeasureText(scoreText, 20);
    DrawText(scoreText, GetScreenWidth() - scoreWidth - 20, 10, 20, GOLD);
    // Affichage du timer en dessous
    char timerText[32];
    sprintf(timerText, "Temps : %.1fs", survivalTime);
    int timerWidth = MeasureText(timerText, 20);
    DrawText(timerText, GetScreenWidth() - timerWidth - 20, 40, 20, DARKGRAY);
}