#ifndef ANIMATION_H
#define ANIMATION_H

#include "gif.h"
#include "config.h"
#include "raylib/raylib.h"

void DrawAnimatedText(float time, const AnimationConfig* config);
void RunMessageAnimation(AnimationConfig* config, int fromWriteInterface);
void SaveAnimationAsGif(const AnimationConfig* config, const char* filename);
bool SaveFileMessageCard(const char* filename, const uint8_t* data, size_t size);

#endif
