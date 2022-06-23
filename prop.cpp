#include  "prop.h"
#include  "raymath.h"
#include  "raylib.h"

prop::prop(Vector2 pos, Texture2D tex)//:
   // worldPos(pos),
    //texture(tex)
{
    worldPos = pos; // to zostało dopisane
    texture = tex;
}

void prop::render(Vector2 knightPos)
{   
    //lokalizacja propu - tak zeby sie nie ruszal
    Vector2 screenPos {Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture,screenPos, 0.f , scale, WHITE);
};

Rectangle prop::GetCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos {Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}