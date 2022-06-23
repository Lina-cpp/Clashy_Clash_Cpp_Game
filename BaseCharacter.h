#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    //konstruktor
    BaseCharacter();

    //reszta zmiennych
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement(); //class #undomovement
    Rectangle GetCollisionRec(); //kolizja postaci - potrzebna do kolizjiz propami
    virtual void tick(float deltaTime);

    bool getAlive(){ return alive; }
    void setAlive(bool isAlive) {alive = isAlive;}

protected:

    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};
    //cofanie postaci #undomovement
    Vector2 worldPosLastFrame{};

    // 1:facing right, -1:facing left
    float rightLeft = 1.f;

    // zmiennie potrzebne do animacji postaci #knightAnimations
    float runningTime;
    int frame;
    int maxFrames = 6;
    float updateTime{1.f / 12.f};
    float speed = 4.f;
    float scale = 4.0f;
    float width{};
    float height{};
    Vector2 velocity{};

private:
bool alive=true;
};

#endif