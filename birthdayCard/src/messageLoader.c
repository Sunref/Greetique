#include <stdio.h>
#include <string.h>
#include "../include/config.h"
#include "../include/messageLoader.h"

// Global variables to store loaded messages
static char loadedMainMessage[256] = MAIN_MESSAGE "";
static char loadedSubMessage[256] = SUB_MESSAGE "";
static char loadedThirdMessage[256] = THIRD_MESSAGE "";
static bool loadedUseHeartBalloons = false;

// Function to load messages from file
void LoadMessagesFromFile(AnimationConfig* config) {
    FILE* file = fopen("animation_config.txt", "r");
    if (file != NULL) {
        char tempBuffer[256];
        int heartBalloons = 0;

        // Read first line (main message)
        if (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL) {
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len-1] == '\n') {
                tempBuffer[len-1] = '\0';
            }
            if (strlen(tempBuffer) > 0) {
                strcpy(loadedMainMessage, tempBuffer);
                strcpy(config->mainMessage, tempBuffer);
            }
        }

        // Read second line (secondary message)
        if (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL) {
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len-1] == '\n') {
                tempBuffer[len-1] = '\0';
            }
            if (strlen(tempBuffer) > 0) {
                strcpy(loadedSubMessage, tempBuffer);
                strcpy(config->subMessage, tempBuffer);
            }
        }

        // Read third line (third message)
        if (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL) {
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len-1] == '\n') {
                tempBuffer[len-1] = '\0';
            }
            if (strlen(tempBuffer) > 0) {
                strcpy(loadedThirdMessage, tempBuffer);
                strcpy(config->thirdMessage, tempBuffer);
            }
        }

        // Read balloons configuration
        if (fscanf(file, "%d", &heartBalloons) == 1) {
            loadedUseHeartBalloons = heartBalloons != 0;
            config->useHeartBalloons = loadedUseHeartBalloons;
        }

        fclose(file);
    }
}

const char* GetMainMessage(void) {
    return loadedMainMessage;
}

const char* GetSubMessage(void) {
    return loadedSubMessage;
}

const char* GetThirdMessage(void) {
    return loadedThirdMessage;
}

bool UseHeartBalloons(void) {
    return loadedUseHeartBalloons;
}
