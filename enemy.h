#include "raylib.h"
#include "BaseCharacter.h"
#include "character.h"

class enemy : public BaseCharacter
{
   public:
     //konstruktor enemy
     enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
     virtual void tick(float deltaTime) override;
     void setTarget(character* character) { target = character;}

   private: 
     //tworzymy pointer to character
     character* target = nullptr;
     float damagePerSec{10.f};
     float radius = 25.f;
};