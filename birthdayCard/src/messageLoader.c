#include "../include/messageLoader.h"
#include <stdio.h>
#include <string.h>

// Buffer for loaded messages
static char loadedMainMessage[256] = "";
static char loadedSubMessage[256] = "";
static char loadedThirdMessage[256] = "";

// Function to load messages from file
int LoadMessagesFromFile(AnimationConfig* config) {
    FILE* file = fopen("animation_config.txt", "r");
    if (file == NULL) {
        return 0;  // Failed to open file
    }

    // Clear buffers
    memset(loadedMainMessage, 0, sizeof(loadedMainMessage));
    memset(loadedSubMessage, 0, sizeof(loadedSubMessage));
    memset(loadedThirdMessage, 0, sizeof(loadedThirdMessage));

    // Read messages from file
    char buffer[256];

    // Read main message
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove the \n
        strncpy(config->mainMessage, buffer, MAX_MESSAGE_LENGTH - 1);
        config->mainMessage[MAX_MESSAGE_LENGTH - 1] = '\0';
    } else {
        fclose(file);
        return 0;
    }

    // Read secondary message
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove o \n
        strncpy(config->subMessage, buffer, MAX_MESSAGE_LENGTH - 1);
        config->subMessage[MAX_MESSAGE_LENGTH - 1] = '\0';
    } else {
        fclose(file);
        return 0;
    }

    // Read third message
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove o \n
        strncpy(config->thirdMessage, buffer, MAX_MESSAGE_LENGTH - 1);
        config->thirdMessage[MAX_MESSAGE_LENGTH - 1] = '\0';
    } else {
        fclose(file);
        return 0;
    }

    // Read balloons configuration
    int heartBalloons;
    if (fscanf(file, "%d", &heartBalloons) == 1) {
        config->useHeartBalloons = heartBalloons != 0;
    } else {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;  // Success
}

// Getter functions for messages
const char* GetMainMessage() {
    return loadedMainMessage;
}

const char* GetSubMessage() {
    return loadedSubMessage;
}

const char* GetThirdMessage() {
    return loadedThirdMessage;
}
