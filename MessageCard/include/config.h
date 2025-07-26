#ifndef CONFIG_H
#define CONFIG_H

#include "raylib/raylib.h"

// Screen dimensions
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 658

// Animation configuration
#define MAX_BALLOONS 20
#define MAX_STARS 50

// Font sizes
#define MAIN_FONT_SIZE 50
#define SUB_FONT_SIZE 30
#define DETAILS_FONT_SIZE 20

// Background color
#define BACKGROUND_COLOR (Color){ 0, 10, 29, 255 }

// Maximum message length
#define MAX_MESSAGE_LENGTH 256

// Configuration structure for messages
typedef struct {
    char mainMessage[MAX_MESSAGE_LENGTH];
    char subMessage[MAX_MESSAGE_LENGTH];
    char detailsMessage[MAX_MESSAGE_LENGTH];
    int useHeartBalloons;
} AnimationConfig;

#endif
