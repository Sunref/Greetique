#ifndef MESSAGE_INTERFACE_H
#define MESSAGE_INTERFACE_H

#include "raylib.h"

// Structure to store animation settings
typedef struct {
    char mainMessage[256];
    char subMessage[256];
    char thirdMessage[256];
    bool useHeartBalloons;
} AnimationConfig;

// Function to run the message input interface
int runMessageInterface(AnimationConfig* config);

#endif
