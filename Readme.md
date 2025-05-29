# Birthday Card Animation

An interactive birthday animation created with Raylib to celebrate special occasions. The app displays colorful animated balloons and stars with a personalized birthday message.

![Screenshot of the app saying in ptbr "Feliz Aniversario Gabriel!!"](./Screenshot.png)

## About the Project

Created as a simple birthday gift, the project evolved so that any user could create interactive commemorative messages in a simple and easy way. The application allows complete customization of messages through an intuitive interface, automatically saving the configurations.

## Features

- Colorful animated balloons that float upward
- Twinkling star background
- Customizable birthday message
- Interface for message configuration
- Cross-platform support (Windows and Linux)
- Automatic builds and releases through GitHub Actions

## Project Structure

```
birthdayCard/
├── animation_config.txt    # File where interface configurations are saved
├── assets/                 # Project resources
├── bin/
│   └── birthday_animation  # Compiled executable
├── build/                  # Compiled object files
├── include/                # Project headers
│   ├── animation.h
│   ├── balloon.h
│   ├── config.h
│   ├── messageInterface.h
│   ├── messageLoader.h
│   └── star.h
├── src/                    # Source code
│   ├── animation.c
│   ├── balloon.c
│   ├── main.c
│   ├── messageInterface.c
│   ├── messageLoader.c
│   └── star.c
├── Makefile
└── README.md
```

## How to Use

1. **Fork the project** to your GitHub account
2. **Clone the repository** to your local machine
3. **In your preferred editor**, run the commands:
   ```bash
   make
   make run
   ```
4. **Configure your message** through the application interface
5. **Your message will be saved** automatically in the `animation_config.txt` file
6. **Commit** your changes to the project
7. **GitHub Actions** will automatically generate an executable (.exe) for Windows

## Dependencies

- **Raylib** and derived libraries
- C compiler (gcc, mingw-w64 for Windows builds)
- Make

## Credits

Created by Fernanda with assistance from Claude AI.
Built with [Raylib](https://www.raylib.com/).

## License

[MIT License](LICENSE)
