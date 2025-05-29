#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

#include "messageInterface.h"

// Function to load messages from saved file
void LoadMessagesFromFile(AnimationConfig* config);

// Functions to get loaded messages
const char* GetMainMessage(void);
const char* GetSubMessage(void);
const char* GetThirdMessage(void);
bool UseHeartBalloons(void);

#endif
