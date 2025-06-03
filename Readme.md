# Card Animation

An interactive card animation created with Raylib to celebrate special occasions. The app displays colorful animated balloons and stars with a personalized message.

![Screenshot of the app saying in ptbr "Feliz Aniversario Gabriel!!"](./Screenshot.png)

## About the Project

Created as a simple birthday gift, the project evolved so that any user could create interactive commemorative messages in a simple and easy way. The application allows complete customization of messages through an intuitive interface, automatically saving the configurations.

## Features

- Colorful animated balloons that float upward
- Twinkling star background
- Customizable message
- Menu interface for choosing between Write and Read modes
- Message editing with return button in animation screen
- Direct animation preview after editing
- Cross-platform support (Windows and Linux)
- Automatic builds and releases through GitHub Actions

## Project Structure

```
MessageCard/
├── animation_config.txt    # File where interface configurations are saved
├── saved_cards/            # Save specific messages here
├── assets/                 # Project resources
├── bin/
│   └── message_animation   # Compiled executable
├── build/                  # Compiled object files
├── include/                # Project headers
│   ├── animation.h
│   ├── balloon.h
│   ├── config.h
│   ├── menuInterface.h
│   ├── messageInterface.h
│   ├── messageLoader.h
│   └── star.h
├── src/                    # Source code
│   ├── animation.c
│   ├── balloon.c
│   ├── main.c
│   ├── menuInterface.c
│   ├── messageInterface.c
│   ├── messageLoader.c
│   └── star.c
└── Makefile
```

## How to Use

1. **Fork the project** to your GitHub account
2. **Clone the repository** to your local machine
3. **In your preferred editor**, run the commands:
   ```bash
   make
   make run
   ```
4. **Configure your message** through the application interface:
   - Choose between Write (new message) or Read (saved messages) mode
   - In Write mode:
     - Customize your message
     - Preview the animation
     - Use the return button to edit your message
     - Changes are previewed instantly
   - In Read mode:
     - View your saved messages with full animation
5. **Your message will be saved** automatically in the `animation_config.txt` file

## How to Share

### Sending Your Card
You can share your created card with others. The message is stored in the `saved_cards/` directory.

#### For Linux Users
1. Locate your card:
   - Find the `message_animation` executable in the `bin/` directory
   - Locate your saved message in `saved_cards/`
2. Share both files:
   - Send both the executable and your saved message file
   - Recipient should keep both files in the same directory
3. Recipients simply need to:
   - Run the executable
   - Click "Read a message"
   - Enjoy your personalized animation!

#### For Windows Users
1. Get the latest release:
   - Go to the [Releases](https://github.com/Sunref/Message-Card/releases) page
   - Download the Windows executable (.exe)
2. Share your card:
   - Send your saved message file from `saved_cards/`
   - Recipients should place the message file in the same directory as the .exe
3. Recipients simply need to:
   - Run the .exe file
   - Click "Read a message"
   - The animation will play automatically!

Note: Make sure both the executable and message file are in the same directory for the card to work properly.

## Dependencies

- **Raylib** and derived libraries
- C compiler (gcc, mingw-w64 for Windows builds)
- Make

## Credits

Created by Fernanda.
Built with [Raylib](https://www.raylib.com/).

## License

[MIT License](LICENSE)
