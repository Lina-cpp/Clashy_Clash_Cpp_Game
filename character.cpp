#include "character.h"
#include "raymath.h"


character::character(int winWidth, int winHeight) 
{
        width = texture.width / maxFrames,
        height = texture.height;

            screenPos = {
    static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
    static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
    };
}




// dalsze deklaracje funkcji character #knight

void character::tick(float deltaTime)
{ 

    // poruszanie mapy #movement
    if (IsKeyDown(KEY_A))velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))velocity.x += 1.0;
    if (IsKeyDown(KEY_W))velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))velocity.y += 1.0;

    //wywołanie tick() które jest wspolny dla gracza i mobow  
    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation;
    if(rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = { 35.f, 55.f};
        weaponCollisionRec = {
            screenPos.x + offset.x,
            screenPos.y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = { 25.f, 55.f};
        weaponCollisionRec = {
            screenPos.x + offset.x - weapon.width * scale,
            screenPos.y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    //draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{screenPos.x + offset.x , screenPos.y + offset.y , weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    /* //weapon hitbox
    DrawRectangleLines(
    weaponCollisionRec.x,
    weaponCollisionRec.y,
    weaponCollisionRec.width,
    weaponCollisionRec.height,
    RED
    );
    */
}

void character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
    
}