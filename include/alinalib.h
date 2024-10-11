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

#include <SDL.h>
#include <SDL_ttf.h>

// ╔══════════════════════════════════════════════════════════╗
// ║                          TYPES                            ║
// ╚══════════════════════════════════════════════════════════╝

// Struct for managing time during frame rendering
typedef struct alinalib__Time alinalib_Time;
typedef struct alinalib__Input alinalib_Input;

// Struct for application context, including window and time
typedef struct
{
    int shouldClose;   // Flag to close the window
    int windowWidth;   // Width of the window
    int windowHeight;  // Height of the window
    float currentFps;  // Current frames per second
    float deltaTime;   // Time between the current and last frame (in seconds)

    // WINDOW
    SDL_Window *window;      // SDL window pointer
    SDL_Renderer *renderer;  // SDL renderer pointer
    // Font
    TTF_Font *defaultFont;
    // TIME
    alinalib_Time *time;    // Time management data
    alinalib_Input *input;  // Input management data
} alinalib_Context;

// Type definitions
typedef struct SDL_Color alinalib_Color;     // rgba color
typedef struct SDL_Point alinalib_Point;     // 2D point
typedef struct SDL_FPoint alinalib_Vector2;  // 2D floating point
typedef struct SDL_Rect alinalib_Rect;       // 2D rectangle
typedef struct SDL_FRect alinalib_FRect;     // 2D floating point rectangle

// ╔══════════════════════════════════════════════════════════╗
// ║                          DEFINE                           ║
// ╚══════════════════════════════════════════════════════════╝

#define ALINALIB_DEFAULT_FONT_SIZE 24
#define MAX_KEYBOARD_KEYS 512
#define MAX_MOUSE_BUTTON 8

// ╔══════════════════════════════════════════════════════════╗
// ║                          COLORS                           ║
// ╚══════════════════════════════════════════════════════════╝

// Predefined colors
extern const alinalib_Color BLACK;  // Black color
extern const alinalib_Color WHITE;  // White color
extern const alinalib_Color RED;    // Red color
extern const alinalib_Color GREEN;  // Green color
extern const alinalib_Color BLUE;   // Blue color

// ╔══════════════════════════════════════════════════════════╗
// ║                           ENUMS                           ║
// ╚══════════════════════════════════════════════════════════╝

typedef enum
{
    KEY_NULL = 0,
    // Alphanumeric keys
    KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,       // '
    KEY_COMMA = SDL_SCANCODE_COMMA,                 // ,
    KEY_MINUS = SDL_SCANCODE_MINUS,                 // -
    KEY_PERIOD = SDL_SCANCODE_PERIOD,               // .
    KEY_SLASH = SDL_SCANCODE_SLASH,                 // /
    KEY_ZERO = SDL_SCANCODE_0,                      // 0
    KEY_ONE = SDL_SCANCODE_1,                       // 1
    KEY_TWO = SDL_SCANCODE_2,                       // 2
    KEY_THREE = SDL_SCANCODE_3,                     // 3
    KEY_FOUR = SDL_SCANCODE_4,                      // 4
    KEY_FIVE = SDL_SCANCODE_5,                      // 5
    KEY_SIX = SDL_SCANCODE_6,                       // 6
    KEY_SEVEN = SDL_SCANCODE_7,                     // 7
    KEY_EIGHT = SDL_SCANCODE_8,                     // 8
    KEY_NINE = SDL_SCANCODE_9,                      // 9
    KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,         // ;
    KEY_EQUAL = SDL_SCANCODE_EQUALS,                // =
    KEY_A = SDL_SCANCODE_A,                         // A
    KEY_B = SDL_SCANCODE_B,                         // B
    KEY_C = SDL_SCANCODE_C,                         // C
    KEY_D = SDL_SCANCODE_D,                         // D
    KEY_E = SDL_SCANCODE_E,                         // E
    KEY_F = SDL_SCANCODE_F,                         // F
    KEY_G = SDL_SCANCODE_G,                         // G
    KEY_H = SDL_SCANCODE_H,                         // H
    KEY_I = SDL_SCANCODE_I,                         // I
    KEY_J = SDL_SCANCODE_J,                         // J
    KEY_K = SDL_SCANCODE_K,                         // K
    KEY_L = SDL_SCANCODE_L,                         // L
    KEY_M = SDL_SCANCODE_M,                         // M
    KEY_N = SDL_SCANCODE_N,                         // N
    KEY_O = SDL_SCANCODE_O,                         // O
    KEY_P = SDL_SCANCODE_P,                         // P
    KEY_Q = SDL_SCANCODE_Q,                         // Q
    KEY_R = SDL_SCANCODE_R,                         // R
    KEY_S = SDL_SCANCODE_S,                         // S
    KEY_T = SDL_SCANCODE_T,                         // T
    KEY_U = SDL_SCANCODE_U,                         // U
    KEY_V = SDL_SCANCODE_V,                         // V
    KEY_W = SDL_SCANCODE_W,                         // W
    KEY_X = SDL_SCANCODE_X,                         // X
    KEY_Y = SDL_SCANCODE_Y,                         // Y
    KEY_Z = SDL_SCANCODE_Z,                         // Z
    KEY_LEFT_BRACKET = SDL_SCANCODE_LEFTBRACKET,    // [
    KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,         // '\'
    KEY_RIGHT_BRACKET = SDL_SCANCODE_RIGHTBRACKET,  // ]
    KEY_GRAVE = SDL_SCANCODE_GRAVE,                 // `
    // Function keys
    KEY_SPACE = SDL_SCANCODE_SPACE,               // Space
    KEY_ESCAPE = SDL_SCANCODE_ESCAPE,             // Esc
    KEY_ENTER = SDL_SCANCODE_RETURN,              // Enter
    KEY_TAB = SDL_SCANCODE_TAB,                   // Tab
    KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,       // Backspace
    KEY_INSERT = SDL_SCANCODE_INSERT,             // Ins
    KEY_DELETE = SDL_SCANCODE_DELETE,             // Del
    KEY_RIGHT = SDL_SCANCODE_RIGHT,               // Cursor right
    KEY_LEFT = SDL_SCANCODE_LEFT,                 // Cursor left
    KEY_DOWN = SDL_SCANCODE_DOWN,                 // Cursor down
    KEY_UP = SDL_SCANCODE_UP,                     // Cursor up
    KEY_PAGE_UP = SDL_SCANCODE_PAGEUP,            // Page up
    KEY_PAGE_DOWN = SDL_SCANCODE_PAGEDOWN,        // Page down
    KEY_HOME = SDL_SCANCODE_HOME,                 // Home
    KEY_END = SDL_SCANCODE_END,                   // End
    KEY_CAPS_LOCK = SDL_SCANCODE_CAPSLOCK,        // Caps lock
    KEY_SCROLL_LOCK = SDL_SCANCODE_SCROLLLOCK,    // Scroll lock
    KEY_NUM_LOCK = SDL_SCANCODE_NUMLOCKCLEAR,     // Num lock
    KEY_PRINT_SCREEN = SDL_SCANCODE_PRINTSCREEN,  // Print screen
    KEY_PAUSE = SDL_SCANCODE_PAUSE,               // Pause
    KEY_F1 = SDL_SCANCODE_F1,                     // F1
    KEY_F2 = SDL_SCANCODE_F2,                     // F2
    KEY_F3 = SDL_SCANCODE_F3,                     // F3
    KEY_F4 = SDL_SCANCODE_F4,                     // F4
    KEY_F5 = SDL_SCANCODE_F5,                     // F5
    KEY_F6 = SDL_SCANCODE_F6,                     // F6
    KEY_F7 = SDL_SCANCODE_F7,                     // F7
    KEY_F8 = SDL_SCANCODE_F8,                     // F8
    KEY_F9 = SDL_SCANCODE_F9,                     // F9
    KEY_F10 = SDL_SCANCODE_F10,                   // F10
    KEY_F11 = SDL_SCANCODE_F11,                   // F11
    KEY_F12 = SDL_SCANCODE_F12,                   // F12
    KEY_LEFT_SHIFT = SDL_SCANCODE_LSHIFT,         // Shift left
    KEY_LEFT_CONTROL = SDL_SCANCODE_LCTRL,        // Control left
    KEY_LEFT_ALT = SDL_SCANCODE_LALT,             // Alt left
    KEY_LEFT_SUPER = SDL_SCANCODE_LGUI,           // Super left
    KEY_RIGHT_SHIFT = SDL_SCANCODE_RSHIFT,        // Shift right
    KEY_RIGHT_CONTROL = SDL_SCANCODE_RCTRL,       // Control right
    KEY_RIGHT_ALT = SDL_SCANCODE_RALT,            // Alt right
    KEY_RIGHT_SUPER = SDL_SCANCODE_RGUI,          // Super right
    KEY_KB_MENU = SDL_SCANCODE_MENU,              // KB menu
    // Keypad keys
    KEY_KP_0 = SDL_SCANCODE_KP_0,                // Keypad 0
    KEY_KP_1 = SDL_SCANCODE_KP_1,                // Keypad 1
    KEY_KP_2 = SDL_SCANCODE_KP_2,                // Keypad 2
    KEY_KP_3 = SDL_SCANCODE_KP_3,                // Keypad 3
    KEY_KP_4 = SDL_SCANCODE_KP_4,                // Keypad 4
    KEY_KP_5 = SDL_SCANCODE_KP_5,                // Keypad 5
    KEY_KP_6 = SDL_SCANCODE_KP_6,                // Keypad 6
    KEY_KP_7 = SDL_SCANCODE_KP_7,                // Keypad 7
    KEY_KP_8 = SDL_SCANCODE_KP_8,                // Keypad 8
    KEY_KP_9 = SDL_SCANCODE_KP_9,                // Keypad 9
    KEY_KP_DECIMAL = SDL_SCANCODE_KP_PERIOD,     // Keypad .
    KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,      // Keypad /
    KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,  // Keypad *
    KEY_KP_SUBTRACT = SDL_SCANCODE_KP_MINUS,     // Keypad -
    KEY_KP_ADD = SDL_SCANCODE_KP_PLUS,           // Keypad +
    KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER,        // Keypad Enter
    KEY_KP_EQUAL = SDL_SCANCODE_KP_EQUALS,       // Keypad =
    // Android key buttons
    KEY_MENU = SDL_SCANCODE_MENU,              // Android menu button
    KEY_VOLUME_UP = SDL_SCANCODE_VOLUMEUP,     // Android volume up button
    KEY_VOLUME_DOWN = SDL_SCANCODE_VOLUMEDOWN  // Android volume down button
} alinalib_Keycode;

typedef enum
{
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT = 1,
    MOUSE_BUTTON_MIDDLE = 2,
    MOUSE_BUTTON_SIDE = 3,
    MOUSE_BUTTON_EXTRA = 4,
    MOUSE_BUTTON_FORWARD = 5,
    MOUSE_BUTTON_BACK = 6,
} alinalib_MouseButton;

#if defined(__cplusplus)
extern "C"
{  // Prevents name mangling in C++
#endif

    // ╔══════════════════════════════════════════════════════════╗
    // ║                  FUNCTION DECLARATIONS                    ║
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
    void alinalib_clear(alinalib_Context *ctx, const alinalib_Color color);
    // Draws an outlined rectangle
    void alinalib_drawRectangle(alinalib_Context *ctx,
                                const alinalib_Rect rect,
                                const alinalib_Color color);
    // Draws a filled rectangle
    void alinalib_drawFilledRectangle(alinalib_Context *ctx,
                                      const alinalib_Rect rect,
                                      const alinalib_Color color);
    // Draws a line between two points
    void alinalib_drawLine(alinalib_Context *ctx,
                           const alinalib_Point p1,
                           const alinalib_Point p2,
                           const alinalib_Color color);

    // ────────────────────────────────────────────────────────────────
    //                             TIME
    // ────────────────────────────────────────────────────────────────

    // Load font
    TTF_Font *alinalib_loadFont(const char *filePath, int size);
    // Dispose font
    void alinalib_disposeFont(TTF_Font *font);
    // Set font size
    void alinalib_setFontSize(TTF_Font *font, int ptsize);
    // Mesure text size
    alinalib_Point alinalib_measureText(const char *text, TTF_Font *font);
    // Draw text by using default font
    void alinalib_drawText(alinalib_Context *ctx,
                           const char *text,
                           const alinalib_Point *position,
                           const alinalib_Color color);
    // Draw custom text using specified font, angle, glow effect
    void alinalib_drawCustomText(alinalib_Context *ctx,
                                 TTF_Font *font,
                                 const char *text,
                                 const alinalib_Point *position,
                                 const alinalib_Point *origin,
                                 const alinalib_Color color,
                                 double angle,
                                 int glowSize,
                                 const alinalib_Color glowColor);

    // ────────────────────────────────────────────────────────────────
    //                             TIME
    // ────────────────────────────────────────────────────────────────

    // Sets the target FPS for rendering
    void alinalib_timeSetTargetFps(alinalib_Context *ctx, int targetFps);

    // ────────────────────────────────────────────────────────────────
    //                             INPUT
    // ────────────────────────────────────────────────────────────────

    // Get keyboard states
    int alinalib_inputIsKeyDown(alinalib_Context *ctx, alinalib_Keycode key);
    int alinalib_inputIsKeyUp(alinalib_Context *ctx, alinalib_Keycode key);
    int alinalib_inputIsKeyPressed(alinalib_Context *ctx, alinalib_Keycode key);
    // Get mouse states
    alinalib_Point alinalib_inputGetMousePosition(alinalib_Context *ctx);
    int alinalib_inputIsMouseButtonDown(alinalib_Context *ctx,
                                        alinalib_MouseButton button);
    int alinalib_inputIsMouseButtonUp(alinalib_Context *ctx,
                                      alinalib_MouseButton button);
    int alinalib_inputIsMouseButtonPressed(alinalib_Context *ctx,
                                           alinalib_MouseButton button);

#if defined(__cplusplus)
}
#endif

#endif  // !ALINALIB_H
