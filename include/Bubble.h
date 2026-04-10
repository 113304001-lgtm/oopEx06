#ifndef BUBBLE_H
#define BUBBLE_H

#include "raylib.h"

class Bubble {
private:
    Vector2 position;
    float radius;
    int points;
    Color color;
    bool active;

    Color generateRandomColor();

public:
    Bubble(float x, float y, float r);
    
    Vector2 getPosition() const;
    float getRadius() const;
    int getPoints() const;
    Color getColor() const;
    bool isActive() const;
    
    void setPosition(float x, float y);
    int pop();
    void drift(float deltaY);
    void draw() const;
    bool containsPoint(float x, float y) const;
};

#endif
