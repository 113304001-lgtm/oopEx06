#include "Bubble.h"
#include <cstdlib>
#include <cstdio>

Color Bubble::generateRandomColor() {
    return Color{
        (unsigned char)(rand() % 155 + 100),
        (unsigned char)(rand() % 155 + 100),
        (unsigned char)(rand() % 200 + 55),
        220
    };
}

Bubble::Bubble(float x, float y, float r) {
    position = {x, y};
    radius = r;
    points = (int)(radius * 0.9f) + 5;
    color = generateRandomColor();
    active = true;
}

Vector2 Bubble::getPosition() const { return position; }
float Bubble::getRadius() const { return radius; }
int Bubble::getPoints() const { return points; }
Color Bubble::getColor() const { return color; }
bool Bubble::isActive() const { return active; }

void Bubble::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

int Bubble::pop() {
    if (!active) return 0;
    active = false;
    return points;
}

void Bubble::drift(float deltaY) {
    position.y += deltaY;
}

void Bubble::draw() const {
    DrawCircleV(position, radius, color);
    DrawCircleLinesV(position, radius, Fade(WHITE, 0.5f));
    DrawCircleV({position.x - radius * 0.2f, position.y - radius * 0.2f}, 
                radius * 0.25f, Fade(WHITE, 0.6f));
    
    char text[8];
    sprintf(text, "+%d", points);
    int fontSize = (int)(radius * 0.45f);
    if (fontSize < 12) fontSize = 12;
    DrawText(text, (int)(position.x - radius * 0.4f), 
             (int)(position.y - radius * 0.2f), fontSize, BLACK);
    DrawText(text, (int)(position.x - radius * 0.42f), 
             (int)(position.y - radius * 0.22f), fontSize, Fade(WHITE, 0.9f));
}

bool Bubble::containsPoint(float x, float y) const {
    float dx = x - position.x;
    float dy = y - position.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}
