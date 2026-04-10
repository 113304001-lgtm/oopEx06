#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "Bubble.h"

class GameManager {
private:
    std::vector<Bubble> bubbles;
    int totalScore;
    float spawnTimer;
    float screenWidth;
    float screenHeight;

    void spawnBubble();
    void updateBubbles(float deltaTime);
    void drawBackground() const;
    void drawUI() const;

public:
    GameManager(int width, int height);
    
    void update(float deltaTime);
    void handleClick(float mouseX, float mouseY);
    void draw() const;
    int getScore() const;
};

#endif
