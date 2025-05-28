#ifndef MESSAGE_INTERFACE_H
#define MESSAGE_INTERFACE_H

#include "raylib.h"

// Estrutura para armazenar as configurações da animação
typedef struct {
    char mainMessage[256];
    char subMessage[256];
    char thirdMessage[256];
    bool useHeartBalloons;
} AnimationConfig;

// Função para executar a interface de entrada de mensagens
int runMessageInterface(AnimationConfig* config);

#endif
