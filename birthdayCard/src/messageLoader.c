#include <stdio.h>
#include <string.h>
#include "../include/config.h"
#include "../include/messageLoader.h"

// Global variables to store the loaded messages
static char loadedMainMessage[256] = MAIN_MESSAGE;
static char loadedSubMessage[256] = SUB_MESSAGE;
static char loadedThirdMessage[256] = THIRD_MESSAGE;

// Function to load messages from file
void LoadMessagesFromFile(void) {
    FILE* file = fopen("messages.txt", "r");
    if (file != NULL) {
        char tempBuffer[256];

        // Read first line (main message)
        if (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL) {
            // Remove newline character if present
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len-1] == '\n') {
                tempBuffer[len-1] = '\0';
            }
            // Only use the loaded message if it's not empty
            if (strlen(tempBuffer) > 0) {
                strcpy(loadedMainMessage, tempBuffer);
            }
            // If empty, keep the default from config.h
        }

        // Read second line (sub message)
        if (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL) {
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len-1] == '\n') {
                tempBuffer[len-1] = '\0';
            }
            // Only use the loaded message if it's not empty
            if (strlen(tempBuffer) > 0) {
                strcpy(loadedSubMessage, tempBuffer);
            }
        }

        // Read third line (third message)
        if (fgets(tempBuffer, sizeof(tempBuffer), file) != NULL) {
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len-1] == '\n') {
                tempBuffer[len-1] = '\0';
            }
            // Only use the loaded message if it's not empty
            if (strlen(tempBuffer) > 0) {
                strcpy(loadedThirdMessage, tempBuffer);
            }
        }

        fclose(file);
    }
    // If file doesn't exist or can't be read, use default messages from config.h
}

// Function to get the loaded messages
const char* GetMainMessage(void) {
    return loadedMainMessage;
}

const char* GetSubMessage(void) {
    return loadedSubMessage;
}

const char* GetThirdMessage(void) {
    return loadedThirdMessage;
}
