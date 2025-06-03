#include "../include/messageLoader.h"
#include <stdio.h>
#include <string.h>

// Buffer para as mensagens carregadas
static char loadedMainMessage[256] = "";
static char loadedSubMessage[256] = "";
static char loadedThirdMessage[256] = "";

// Função para carregar mensagens do arquivo
int LoadMessagesFromFile(AnimationConfig* config) {
    FILE* file = fopen("animation_config.txt", "r");
    if (file == NULL) {
        return 0;  // Falha ao abrir o arquivo
    }

    // Limpa os buffers
    memset(loadedMainMessage, 0, sizeof(loadedMainMessage));
    memset(loadedSubMessage, 0, sizeof(loadedSubMessage));
    memset(loadedThirdMessage, 0, sizeof(loadedThirdMessage));

    // Lê as mensagens do arquivo
    char buffer[256];

    // Lê a mensagem principal
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove o \n
        strncpy(config->mainMessage, buffer, MAX_MESSAGE_LENGTH - 1);
        config->mainMessage[MAX_MESSAGE_LENGTH - 1] = '\0';
    } else {
        fclose(file);
        return 0;
    }

    // Lê a mensagem secundária
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove o \n
        strncpy(config->subMessage, buffer, MAX_MESSAGE_LENGTH - 1);
        config->subMessage[MAX_MESSAGE_LENGTH - 1] = '\0';
    } else {
        fclose(file);
        return 0;
    }

    // Lê a terceira mensagem
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Remove o \n
        strncpy(config->thirdMessage, buffer, MAX_MESSAGE_LENGTH - 1);
        config->thirdMessage[MAX_MESSAGE_LENGTH - 1] = '\0';
    } else {
        fclose(file);
        return 0;
    }

    // Lê a configuração dos balões
    int heartBalloons;
    if (fscanf(file, "%d", &heartBalloons) == 1) {
        config->useHeartBalloons = heartBalloons != 0;
    } else {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;  // Sucesso
}

// Funções getter para as mensagens
const char* GetMainMessage() {
    return loadedMainMessage;
}

const char* GetSubMessage() {
    return loadedSubMessage;
}

const char* GetThirdMessage() {
    return loadedThirdMessage;
}
