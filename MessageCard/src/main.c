#include "../include/raylib/raylib.h"
#include "../include/animation.h"
#include "../include/messageInterface.h"
#include "../include/config.h"

int main(int argc, char *argv[]) {
    (void)argc; (void)argv; // Suppress unused parameter warnings

    // Create configuration structure
    AnimationConfig config = {0};

    // Go directly to message interface, then animation
    while (1) {
        if (runMessageInterface(&config)) {
            RunMessageAnimation(&config, 1);  // Always from write interface now
        } else {
            break; // Exit if user closes message interface
        }
    }

    return 0;
}