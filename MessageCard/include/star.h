#ifndef STAR_H
#define STAR_H

#include "raylib/raylib.h"

// Star structure definition
typedef struct {
    Vector2 position;
    float radius;
    Color color;
    float rotation;
    float rotationSpeed;
    float scale;
    float scaleSpeed;
} Star;

// Star functions
void InitializeStars(Star stars[], int maxStars, int screenWidth, int screenHeight);
void UpdateStars(Star stars[], int maxStars, float time);
void DrawStars(Star stars[], int maxStars);

#endif
