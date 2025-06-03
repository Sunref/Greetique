#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

#include "config.h"

// Função para carregar mensagens do arquivo
int LoadMessagesFromFile(AnimationConfig* config);

// Funções getter para as mensagens
const char* GetMainMessage(void);
const char* GetSubMessage(void);
const char* GetThirdMessage(void);

#endif
