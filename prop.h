#include "raylib.h"

class prop
{
    public:
        prop(Vector2 pos, Texture2D tex);
        void render(Vector2 knightPos);
        Rectangle GetCollisionRec(Vector2 knightPos);

    private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale = 4.0f;
};