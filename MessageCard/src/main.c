#include "../include/config.h"
#include "../include/animation.h"
#include "../include/messageInterface.h"

int main(int argc, char *argv[]) {

    (void)argc; (void)argv;

    AnimationConfig config = {0};

    while (1) {
        if (runMessageInterface(&config)) {
            RunMessageAnimation(&config, 1);
        } else {
            break; // Exit if user closes interface
        }
    }

    return 0;

}
