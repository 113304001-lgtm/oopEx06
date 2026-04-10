#include "GameManager.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

const float SPAWN_DELAY = 0.25f;
const float DRIFT_SPEED = 35.0f;
const int MIN_RADIUS = 16;
const int MAX_RADIUS = 48;
const int MAX_BUBBLES = 400;

GameManager::GameManager(int width, int height) {
    totalScore = 0;
    spawnTimer = 0.0f;
    screenWidth = (float)width;
    screenHeight = (float)height;
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < 30; i++) {
        float radius = MIN_RADIUS + (rand() % (MAX_RADIUS - MIN_RADIUS + 1));
        float x = radius + (rand() % (int)(screenWidth - radius * 2));
        float y = radius + (rand() % (int)(screenHeight - radius * 2));
        bubbles.emplace_back(x, y, radius);
    }
}

void GameManager::spawnBubble() {
    if (bubbles.size() >= MAX_BUBBLES) {
        bubbles.erase(bubbles.begin(), bubbles.begin() + 10);
    }
    
    float radius = MIN_RADIUS + (rand() % (MAX_RADIUS - MIN_RADIUS + 1));
    float x = radius + (rand() % (int)(screenWidth - radius * 2));
    float y = screenHeight - radius - 5;
    
    bubbles.emplace_back(x, y, radius);
}

void GameManager::updateBubbles(float deltaTime) {
    float drift = DRIFT_SPEED * deltaTime;
    
    for (int i = 0; i < (int)bubbles.size(); i++) {
        if (!bubbles[i].isActive()) continue;
        
        bubbles[i].drift(-drift);
        
        Vector2 pos = bubbles[i].getPosition();
        float r = bubbles[i].getRadius();
        
        if (pos.y + r < 0 || pos.y - r > screenHeight ||
            pos.x + r < 0 || pos.x - r > screenWidth) {
            bubbles.erase(bubbles.begin() + i);
            i--;
        }
    }
}

void GameManager::drawBackground() const {
    for (int i = 0; i < screenHeight; i++) {
        float t = (float)i / screenHeight;
        Color gradColor = {
            (unsigned char)(30 + (int)(50 * t)),
            (unsigned char)(80 + (int)(40 * t)),
            (unsigned char)(110 + (int)(60 * t)),
            255
        };
        DrawLine(0, i, (int)screenWidth, i, gradColor);
    }
}

void GameManager::drawUI() const {
    DrawRectangle(10, 10, 220, 70, Fade(BLACK, 0.6f));
    DrawRectangleLines(10, 10, 220, 70, Fade(WHITE, 0.8f));
    DrawText("SCORE:", 25, 25, 30, RAYWHITE);
    
    char scoreStr[16];
    sprintf(scoreStr, "%d", totalScore);
    DrawText(scoreStr, 25, 55, 40, GOLD);
    
    DrawText("Click any bubble to POP!", 
             (int)(screenWidth / 2 - 150), 
             (int)(screenHeight - 40), 
             20, Fade(RAYWHITE, 0.9f));
}

void GameManager::update(float deltaTime) {
    spawnTimer += deltaTime;
    if (spawnTimer >= SPAWN_DELAY) {
        spawnBubble();
        spawnTimer = 0.0f;
    }
    
    updateBubbles(deltaTime);
}

void GameManager::handleClick(float mouseX, float mouseY) {
    for (int i = (int)bubbles.size() - 1; i >= 0; i--) {
        if (!bubbles[i].isActive()) continue;
        
        if (bubbles[i].containsPoint(mouseX, mouseY)) {
            totalScore += bubbles[i].pop();
            bubbles.erase(bubbles.begin() + i);
            break;
        }
    }
}

void GameManager::draw() const {
    drawBackground();
    
    for (const auto& bubble : bubbles) {
        if (bubble.isActive()) {
            bubble.draw();
        }
    }
    
    drawUI();
}

int GameManager::getScore() const {
    return totalScore;
}
