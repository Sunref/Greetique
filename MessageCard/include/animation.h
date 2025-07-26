#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib/raylib.h"
#include "config.h"
#include "gif.h"

// Functions for text animation
void DrawAnimatedText(float time, const AnimationConfig* config);
void RunMessageAnimation(AnimationConfig* config, int fromWriteInterface);

// Function for GIF creation
void SaveAnimationAsGif(const AnimationConfig* config, const char* filename);

// Utility function for file saving
bool SaveFileMessageCard(const char* filename, const uint8_t* data, size_t size);

#endif
