#ifndef BALLOON_H
#define BALLOON_H

#include "raylib.h"

typedef enum {
    BALLOON_OVAL,
    BALLOON_HEART
} BalloonShape;

typedef struct {
    Vector2 position;
    float radius;
    Color color;
    float speed;
    BalloonShape shape;
} Balloon;

void InitializeBalloons(Balloon balloons[], int maxBalloons, int screenWidth, int screenHeight, bool useHeartBalloons);
void UpdateBalloons(Balloon balloons[], int maxBalloons, int screenHeight, float time);
void DrawBalloons(Balloon balloons[], int maxBalloons, float time);

#endif
