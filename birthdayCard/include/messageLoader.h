#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

#include "config.h"

// Function to load messages from file
int LoadMessagesFromFile(AnimationConfig* config);

// Getter functions for messages
const char* GetMainMessage(void);
const char* GetSubMessage(void);
const char* GetThirdMessage(void);

#endif
