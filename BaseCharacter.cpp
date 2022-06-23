#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
    
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}



Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

     // update animation frames
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

        if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + velocity

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

  

    // rysowanie postaci #knight
    Rectangle knightSource{frame * width, 0.f, rightLeft * width, height}; // który sprite sheet ma byc uzyty
    // gdzie narysowac postac - lokalizacja || 4.0f to skalowanie postaci
    Rectangle knightDest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.f, WHITE);
}


