# alinalib 🎮

**alinalib** is an experimental 2D game engine library built as a wrapper around SDL2. This project is a work in progress, primarily developed for fun and to practice and improve my knowledge of C.

## Features ✨
- A simple abstraction over SDL2 for 2D game development.
- Single-header library (`alinalib.h`) for ease of use.
- Handles window creation, input, and rendering.
- Clean and minimal design to keep things simple and easy to extend.
- **Huge inspiration from [Raylib](https://www.raylib.com/)**, aiming for simplicity and ease of use in game development.

## Status 🚧
This library is currently in development and is not ready for production use. Expect incomplete features and breaking changes as the code evolves.

## Motivation 💡
alinalib is a personal project created to experiment with low-level game development concepts in C. The goal is to deepen my understanding of game engine architecture and systems programming while working with SDL2. A lot of inspiration comes from Raylib's philosophy of creating a minimal, easy-to-use, and self-contained library for game development.

## Requirements 📋
- [SDL2](https://www.libsdl.org/)
- A C compiler (e.g., GCC or Clang)
- CMake 3.10 or later

## Building the Library with CMake ⚙️

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/alinalib.git
    ```

2. Navigate to the project directory:
    ```bash
    cd alinalib
    ```

3. Create a build directory:
    ```bash
    mkdir build && cd build
    ```

4. Generate build files using CMake:
    ```bash
    cmake ..
    ```

5. Build the project:
    ```bash
    cmake --build .
    ```

### Obtaining `libalinalib.a` 📦
After building, you can find the `libalinalib.a` static library in the `build` directory. You can link this library to your projects:
```bash
/path/to/alinalib/build/libalinalib.a
```

## Usage 📖
Once built, you can include `alinalib.h` directly in your C projects and link the compiled `libalinalib.a` library.

### Example
Include the header in your C file:
```c
#include "alinalib.h"
```
Link your project with `libalinalib.a`:

## Contributing 🤝
This project is not accepting external contributions at this time, as it is for personal learning and experimentation.

## License 📄
This project is licensed under the MIT License. See the `LICENSE` file for details.
