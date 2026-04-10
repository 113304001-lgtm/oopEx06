#include "raylib.h"
#include <iostream>
#include "GameManager.h"

int main() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bubble Pop");
    SetTargetFPS(60);
    
    GameManager game(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            game.handleClick(mousePos.x, mousePos.y);
        }
        
        game.update(deltaTime);
        
        BeginDrawing();
        game.draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
