# Birthday Card Animation

An interactive birthday animation created with Raylib to celebrate Gabriel's birthday. The app displays colorful animated balloons and stars with a personalized birthday message.

![Screenshot of the app saying in ptbr "Feliz Aniversario Gabriel!!"](./Screenshot.png)

## Features

- Colorful animated balloons that float upward
- Twinkling star background
- Customizable birthday message
- Cross-platform support (Windows and Linux)
- Automatic builds and releases through GitHub Actions

## Getting Started

### Running the Application

1. Download the latest release for your platform (Windows or Linux) from the [Releases page](https://github.com/user/Birthday-Card/releases)
2. Run the executable:
   - On Windows: Double-click `aniversario.exe`
        - On Windows you will recive an alert because ...
   - On Linux: Open terminal, navigate to the download location with cd `cd ./Downloads`
   and run `chmod +x ./aniversario` for
   and run `./aniversario`


### Building from Source

#### Prerequisites

- C compiler (gcc, mingw-w64 for Windows builds)
- Raylib development libraries
- CMake (optional, for building Raylib)

#### Build Steps

1. Clone this repository
2. Install Raylib according to your platform
3. Build the application:
   ```bash
   gcc -o aniversario aniversario.c -lraylib -lm -lpthread -ldl
   ```

## Customization

To personalize this birthday card for someone else:

1. Fork this repository (make sure to keep it public for GitHub Actions to work properly)
2. Modify the text in `aniversario.c` to change the displayed message
3. Update the release-notes.md file to document your changes
4. Commit and push to the experimental branch

The GitHub Actions workflow will automatically build both Windows and Linux versions and create a new release.

## Automated Releases

This project uses GitHub Actions to:
- Build the application for both Windows and Linux platforms
- Create versioned releases with downloadable executables
- Maintain release notes history

To trigger a new release, simply update the `release-notes.md` file and push to the experimental branch.

## Credits

Created by Fernanda with assistance from Claude AI.
Built with [Raylib](https://www.raylib.com/).

## License

[MIT License](LICENSE)