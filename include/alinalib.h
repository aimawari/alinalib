#ifndef ALINALIB_H
#define ALINALIB_H

// ╔══════════════════════════════════════════════════════════╗
// ║                         alinalib                          ║
// ╠══════════════════════════════════════════════════════════╣
// ║                                                          ║
// ║   alinalib is an experimental 2D game engine library     ║
// ║   built as a wrapper around SDL2. This project is a      ║
// ║   work in progress, primarily developed for fun and to    ║
// ║   practice and improve my knowledge of C.                ║
// ║                                                          ║
// ╚══════════════════════════════════════════════════════════╝

#include <SDL2/SDL.h>

// ╔══════════════════════════════════════════════════════════╗
// ║                          TYPES                            ║
// ╚══════════════════════════════════════════════════════════╝

// Struct for managing time during frame rendering
typedef struct Time
{
    Uint32 frameStart;  // Time when the current frame started
    Uint32 frameTime;   // Time taken to render the current frame (in ms)
    float deltaTime;    // Time between the current and last frame (in seconds)

    // FPS calculation variables
    int frameCount;       // Number of frames in the last second
    Uint32 fpsStartTime;  // Time when FPS was last calculated
    float currentFps;     // Current frames per second

    // Frame rate control
    int targetFps;  // Desired frames per second
} alinalib_Time;

// Struct for application context, including window and time
typedef struct
{
    // WINDOW
    SDL_Window *window;      // SDL window pointer
    SDL_Renderer *renderer;  // SDL renderer pointer
    int shouldClose;         // Flag to close the window
    int windowWidth;         // Width of the window
    int windowHeight;        // Height of the window

    // TIME
    alinalib_Time time;  // Time management data
} alinalib_Context;

// Struct for representing a color with RGBA values
typedef struct
{
    Uint8 r;  // Red component (0-255)
    Uint8 g;  // Green component (0-255)
    Uint8 b;  // Blue component (0-255)
    Uint8 a;  // Alpha component (0-255)
} alinalib_Color;

// Type definitions for SDL point and rectangle structures
typedef struct SDL_Point alinalib_Point;    // 2D point
typedef struct SDL_FPoint alinalib_FPoint;  // 2D floating point
typedef struct SDL_Rect alinalib_Rect;      // 2D rectangle
typedef struct SDL_FRect alinalib_FRect;    // 2D floating point rectangle

// ╔══════════════════════════════════════════════════════════╗
// ║                          COLORS                           ║
// ╚══════════════════════════════════════════════════════════╝

// Predefined colors
extern const alinalib_Color BLACK;  // Black color
extern const alinalib_Color WHITE;  // White color
extern const alinalib_Color RED;    // Red color
extern const alinalib_Color GREEN;  // Green color
extern const alinalib_Color BLUE;   // Blue color

#if defined(__cplusplus)
extern "C"
{  // Prevents name mangling in C++
#endif

    // ╔══════════════════════════════════════════════════════════╗
    // ║                  FUNCTION DECLARATIONS                  ║
    // ╚══════════════════════════════════════════════════════════╝

    // ────────────────────────────────────────────────────────────────
    //                        WINDOW, CONTEXT, RENDERER
    // ────────────────────────────────────────────────────────────────

    // Initializes the app context with a window and renderer
    alinalib_Context *alinalib_initContext(const char *title,
                                           int width,
                                           int height);
    // Cleans up the resources used by the app context
    void alinalib_cleanupContext(alinalib_Context *ctx);
    // Starts a new frame for rendering
    void alinalib_startFrame(alinalib_Context *ctx);
    // Ends the current frame and does any necessary updates
    void alinalib_endFrame(alinalib_Context *ctx);

    // ────────────────────────────────────────────────────────────────
    //                             GRAPHIC
    // ────────────────────────────────────────────────────────────────

    // Clears the screen with a specified color
    void alinalib_clear(alinalib_Context *ctx, alinalib_Color color);
    // Draws an outlined rectangle
    void alinalib_drawRectangle(alinalib_Context *ctx,
                                alinalib_Rect rect,
                                alinalib_Color color);
    // Draws a filled rectangle
    void alinalib_drawFilledRectangle(alinalib_Context *ctx,
                                      alinalib_Rect rect,
                                      alinalib_Color color);
    // Draws a line between two points
    void alinalib_drawLine(alinalib_Context *ctx,
                           alinalib_Point p1,
                           alinalib_Point p2,
                           alinalib_Color color);

    // ────────────────────────────────────────────────────────────────
    //                             TIME
    // ────────────────────────────────────────────────────────────────

    // Sets the target FPS for rendering
    void alinalib_timeSetTargetFps(alinalib_Time *time, int targetFps);

#if defined(__cplusplus)
}
#endif

#endif  // !ALINALIB_H
