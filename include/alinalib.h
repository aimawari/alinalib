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
typedef struct Time {
  Uint32 frame_start; // Time when the current frame started
  Uint32 frame_time;  // Time taken to render the current frame (in ms)
  float delta_time;   // Time between the current and last frame (in seconds)

  // FPS calculation variables
  int frame_count;       // Number of frames in the last second
  Uint32 fps_start_time; // Time when FPS was last calculated
  float current_fps;     // Current frames per second

  // Frame rate control
  int target_fps; // Desired frames per second
} alinalib_time;

// Struct for application context, including window and time
typedef struct {
  // WINDOW
  SDL_Window *window;     // SDL window pointer
  SDL_Renderer *renderer; // SDL renderer pointer
  int should_close;       // Flag to close the window
  int window_width;       // Width of the window
  int window_height;      // Height of the window

  // TIME
  alinalib_time time; // Time management data
} alinalib_context;

// Struct for representing a color with RGBA values
typedef struct {
  Uint8 r; // Red component (0-255)
  Uint8 g; // Green component (0-255)
  Uint8 b; // Blue component (0-255)
  Uint8 a; // Alpha component (0-255)
} alinalib_color;

// Type definitions for SDL point and rectangle structures
typedef struct SDL_Point alinalib_point;   // 2D point
typedef struct SDL_FPoint alinalib_fpoint; // 2D floating point
typedef struct SDL_Rect alinalib_rect;     // 2D rectangle
typedef struct SDL_FRect alinalib_frect;   // 2D floating point rectangle

// ╔══════════════════════════════════════════════════════════╗
// ║                          COLORS                           ║
// ╚══════════════════════════════════════════════════════════╝

// Predefined colors
extern const alinalib_color BLACK; // Black color
extern const alinalib_color WHITE; // White color
extern const alinalib_color RED;   // Red color
extern const alinalib_color GREEN; // Green color
extern const alinalib_color BLUE;  // Blue color

#if defined(__cplusplus)
extern "C" { // Prevents name mangling in C++
#endif

// ╔══════════════════════════════════════════════════════════╗
// ║                  FUNCTION DECLARATIONS                  ║
// ╚══════════════════════════════════════════════════════════╝

// ────────────────────────────────────────────────────────────────
//                        WINDOW, CONTEXT, RENDERER
// ────────────────────────────────────────────────────────────────

// Initializes the app context with a window and renderer
alinalib_context *alinalib_init_context(const char *title, int width,
                                        int height);
// Cleans up the resources used by the app context
void alinalib_cleanup_context(alinalib_context *ctx);
// Starts a new frame for rendering
void alinalib_start_frame(alinalib_context *ctx);
// Ends the current frame and does any necessary updates
void alinalib_end_frame(alinalib_context *ctx);

// ────────────────────────────────────────────────────────────────
//                             GRAPHIC
// ────────────────────────────────────────────────────────────────

// Clears the screen with a specified color
void alinalib_clear(alinalib_context *ctx, alinalib_color color);
// Draws an outlined rectangle
void alinalib_draw_rectangle(alinalib_context *ctx, alinalib_rect rect,
                             alinalib_color color);
// Draws a filled rectangle
void alinalib_draw_filled_rectangle(alinalib_context *ctx, alinalib_rect rect,
                                    alinalib_color color);
// Draws a line between two points
void alinalib_draw_line(alinalib_context *ctx, alinalib_point p1,
                        alinalib_point p2, alinalib_color color);

// ────────────────────────────────────────────────────────────────
//                             TIME
// ────────────────────────────────────────────────────────────────

// Initializes time management variables
void alinalib_time_init(alinalib_time *time);
// Starts the timer for the current frame
void alinalib_time_start_frame(alinalib_time *time);
// Ends the timer for the current frame and updates time data
void alinalib_time_end_frame(alinalib_time *time);
// Sets the target FPS for rendering
void alinalib_time_set_target_fps(alinalib_time *time, int target_fps);

#if defined(__cplusplus)
}
#endif

#endif // !ALINALIB_H
