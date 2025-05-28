#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

// Function to load messages from the saved file
void LoadMessagesFromFile(void);

// Functions to get the loaded messages
const char* GetMainMessage(void);
const char* GetSubMessage(void);
const char* GetThirdMessage(void);

#endif // MESSAGE_LOADER_H
