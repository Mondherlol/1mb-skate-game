#include "player.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 60
#define DISPLAY_SCALE 2.0f
#define DISPLAY_WIDTH (PLAYER_WIDTH * DISPLAY_SCALE)
#define DISPLAY_HEIGHT (PLAYER_HEIGHT * DISPLAY_SCALE)
#define GROUND_Y 380
#define GRAVITY 0.5f
#define JUMP_FORCE 12.0f
#define FRAME_SPEED 10
#define MAX_FRAMES 4
#define JUMP_BUFFER_FRAMES 6

// Variable pour la texture du sprite
static Texture2D spriteSheet;

Player InitPlayer()
{
    spriteSheet = LoadTexture("../assets/Conan_Sprite_Skate.png");

    Player player = {
        .position = {200, GROUND_Y - PLAYER_HEIGHT},
        .velocityY = 0,
        .isJumping = false,
        .frameRec = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
        .frameCounter = 0,
        .currentFrame = 0,
        .offset = {0, 10},
        .jumpBufferCounter = 0};

    return player;
}

void UpdatePlayer(Player *player)
{
    float delta = GetFrameTime();

    if (++player->frameCounter >= FRAME_SPEED)
    {
        player->frameCounter = 0;
        player->currentFrame = (player->currentFrame + 1) % MAX_FRAMES;
        player->frameRec.x = player->currentFrame * player->frameRec.width;
    }

    if (IsKeyPressed(KEY_UP))
    {
        player->jumpBufferCounter = JUMP_BUFFER_FRAMES;
    }
    else if (player->jumpBufferCounter > 0)
    {
        player->jumpBufferCounter--;
    }

    if (player->jumpBufferCounter > 0 && !player->isJumping)
    {
        player->velocityY = -JUMP_FORCE;
        player->isJumping = true;
        player->jumpBufferCounter = 0;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        player->position.x += 5.0f;
        if (player->position.x > 800 - PLAYER_WIDTH)
            player->position.x = 800 - PLAYER_WIDTH;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        player->position.x -= 5.0f;
        if (player->position.x < 0)
            player->position.x = 0;
    }

    player->velocityY += GRAVITY;
    player->position.y += player->velocityY;

    if (player->position.y >= GROUND_Y - PLAYER_HEIGHT)
    {
        player->position.y = GROUND_Y - PLAYER_HEIGHT;
        player->velocityY = 0;
        player->isJumping = false;
    }
}

void DrawPlayer(Player *player)
{
    Vector2 displayPos = {
        player->position.x - (DISPLAY_WIDTH - PLAYER_WIDTH) / 2 + player->offset.x,
        player->position.y - (DISPLAY_HEIGHT - PLAYER_HEIGHT) + player->offset.y};

    Rectangle destRec = {
        displayPos.x,
        displayPos.y,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT};

    DrawTexturePro(spriteSheet, player->frameRec, destRec, (Vector2){0, 0}, 0, WHITE);
    // DrawRectangle(player->position.x, player->position.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);
}

void UnloadPlayer()
{
    UnloadTexture(spriteSheet);
}