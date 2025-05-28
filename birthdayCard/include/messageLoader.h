#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

#include "messageInterface.h"

// Função para carregar mensagens do arquivo salvo
void LoadMessagesFromFile(AnimationConfig* config);

// Funções para obter as mensagens carregadas
const char* GetMainMessage(void);
const char* GetSubMessage(void);
const char* GetThirdMessage(void);
bool UseHeartBalloons(void);

#endif
