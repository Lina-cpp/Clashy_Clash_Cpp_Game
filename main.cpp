#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

main()
{
    // Deklaracja okna
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    // Zmienne mapy #rysowanieMapy
    Texture2D map = LoadTexture("nature_tileset/worldMap.png");
    Vector2 mapPos{0, 0};
    const float mapScale = 4.0f;

    character knight(windowWidth, windowHeight);

    //rysowanie propu

    
        prop props[2]{
            prop(Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")),
            prop(Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")) 
       };

    //rysujemy goblina #goblin
    enemy goblin{
        Vector2{800.f, 300.f},  
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")    
    };
    enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png") 
    };

        //enemy array
        enemy* enemies[]{
            &goblin,
            &slime
        };
        //targeting enemies to knight
        for (auto enemy : enemies)
        {
            enemy->setTarget(&knight);
        }
        



    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // mapa #rysowanieMapy
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        //rysowanie propow
        for(auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        //dentka dla knighta
        if(!knight.getAlive()) //char is dead
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else //char is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5 );
            DrawText( knightsHealth.c_str(), 55.f, 45.f, 40, RED );
        }

        knight.tick(GetFrameTime());

        //sprawdzanie czy postac wyszla poza ramy mapy
        if(knight.getWorldPos().x < 0.f ||
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + windowWidth > map.width * mapScale ||
           knight.getWorldPos().y + windowHeight > map.width * mapScale)
        {
            knight.undoMovement();
        }

        //check prop collisions
        for(auto prop : props)
        {
           if (CheckCollisionRecs( prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec() ))
            {
                knight.undoMovement();
            };

        };

        //tutaj zrobic fora aby loopowal po wszystkich mobach
        for( auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )
        {
            for (auto enemy : enemies)
            {
                           
                if( CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeaponCollisionRec()) ) 
                {
                    enemy->setAlive(false);
                }

            }

        }


        EndDrawing();
    }
    CloseWindow();
}