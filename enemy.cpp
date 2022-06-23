#include "enemy.h"
#include "BaseCharacter.h"
#include "raymath.h"

enemy::enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames,
    height = texture.height;
    speed = 3.f;
}

void enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    //make "toTarget" vector
    velocity = Vector2Subtract(target->getScreenPos(), screenPos);
    if ( Vector2Length(velocity) < radius ) velocity = {};
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);

    if( CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec() ) )
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}
