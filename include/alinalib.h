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

// ╔══════════════════════════════════════════════════════════╗
// ║                          TYPES                            ║
// ╚══════════════════════════════════════════════════════════╝

typedef struct alinalib_TTFFont alinalib_TTFFont;

typedef struct alinalib_Time
{
    unsigned int frameStart;  // Time when the current frame started
    unsigned int frameTime;   // Time taken to render the current frame (in ms)

    // FPS calculation variables
    int frameCount;             // Number of frames in the last second
    unsigned int fpsStartTime;  // Time when FPS was last calculated

    // Frame rate control
    int targetFps;  // Desired frames per second
} alinalib_Time;

typedef struct alinalib__KeyboardInput alinalib_KeyboardInput;
typedef struct alinalib__MouseInput alinalib_MouseInput;

typedef struct alinalib__Input
{
    alinalib_KeyboardInput *keyboard;
    alinalib_MouseInput *mouse;
} alinalib_Input;

// Struct for application context, including window and time
typedef struct
{
    int shouldClose;   // Flag to close the window
    int windowWidth;   // Width of the window
    int windowHeight;  // Height of the window
    float currentFps;  // Current frames per second
    float deltaTime;   // Time between the current and last frame (in seconds)

    // Font
    alinalib_TTFFont *defaultFont;
    // WINDOW
    void *window;    // SDL window pointer
    void *renderer;  // SDL renderer pointer
    // TIME
    alinalib_Time *time;    // Time management data
    alinalib_Input *input;  // Input management data
} alinalib_Context;

// Type definitions
typedef struct alinalib_Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} alinalib_Color;  // rgba color

typedef struct alinalib_Vector2
{
    float x;
    float y;
} alinalib_Vector2;  // 2D point

typedef struct alinalib_Rect
{
    float x;
    float y;
    float w;
    float h;
} alinalib_Rect;  // 2D rectangle

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
    KEY_NULL = 0,  // Key: NULL, used for no key pressed
    // Alphanumeric keys
    KEY_APOSTROPHE = 39,     // Key: '
    KEY_COMMA = 44,          // Key: ,
    KEY_MINUS = 45,          // Key: -
    KEY_PERIOD = 46,         // Key: .
    KEY_SLASH = 47,          // Key: /
    KEY_ZERO = 82,           // Key: 0
    KEY_ONE = 83,            // Key: 1
    KEY_TWO = 84,            // Key: 2
    KEY_THREE = 85,          // Key: 3
    KEY_FOUR = 86,           // Key: 4
    KEY_FIVE = 87,           // Key: 5
    KEY_SIX = 88,            // Key: 6
    KEY_SEVEN = 89,          // Key: 7
    KEY_EIGHT = 90,          // Key: 8
    KEY_NINE = 91,           // Key: 9
    KEY_SEMICOLON = 59,      // Key: ;
    KEY_EQUAL = 61,          // Key: =
    KEY_A = 4,               // Key: A | a
    KEY_B = 5,               // Key: B | b
    KEY_C = 6,               // Key: C | c
    KEY_D = 7,               // Key: D | d
    KEY_E = 8,               // Key: E | e
    KEY_F = 9,               // Key: F | f
    KEY_G = 10,              // Key: G | g
    KEY_H = 11,              // Key: H | h
    KEY_I = 12,              // Key: I | i
    KEY_J = 13,              // Key: J | j
    KEY_K = 14,              // Key: K | k
    KEY_L = 15,              // Key: L | l
    KEY_M = 16,              // Key: M | m
    KEY_N = 17,              // Key: N | n
    KEY_O = 18,              // Key: O | o
    KEY_P = 19,              // Key: P | p
    KEY_Q = 20,              // Key: Q | q
    KEY_R = 21,              // Key: R | r
    KEY_S = 22,              // Key: S | s
    KEY_T = 23,              // Key: T | t
    KEY_U = 24,              // Key: U | u
    KEY_V = 25,              // Key: V | v
    KEY_W = 26,              // Key: W | w
    KEY_X = 27,              // Key: X | x
    KEY_Y = 28,              // Key: Y | y
    KEY_Z = 29,              // Key: Z | z
    KEY_LEFT_BRACKET = 30,   // Key: [
    KEY_BACKSLASH = 31,      // Key: '\'
    KEY_RIGHT_BRACKET = 32,  // Key: ]
    KEY_GRAVE = 33,          // Key: `
    // Function keys
    KEY_SPACE = 44,           // Key: Space
    KEY_ESCAPE = 41,          // Key: Esc
    KEY_ENTER = 40,           // Key: Enter
    KEY_TAB = 43,             // Key: Tab
    KEY_BACKSPACE = 42,       // Key: Backspace
    KEY_INSERT = 45,          // Key: Ins
    KEY_DELETE = 46,          // Key: Del
    KEY_RIGHT = 79,           // Key: Cursor right
    KEY_LEFT = 80,            // Key: Cursor left
    KEY_DOWN = 81,            // Key: Cursor down
    KEY_UP = 82,              // Key: Cursor up
    KEY_PAGE_UP = 83,         // Key: Page up
    KEY_PAGE_DOWN = 84,       // Key: Page down
    KEY_HOME = 85,            // Key: Home
    KEY_END = 86,             // Key: End
    KEY_CAPS_LOCK = 57,       // Key: Caps lock
    KEY_SCROLL_LOCK = 70,     // Key: Scroll lock
    KEY_NUM_LOCK = 83,        // Key: Num lock
    KEY_PRINT_SCREEN = 69,    // Key: Print screen
    KEY_PAUSE = 84,           // Key: Pause
    KEY_F1 = 58,              // Key: F1
    KEY_F2 = 59,              // Key: F2
    KEY_F3 = 60,              // Key: F3
    KEY_F4 = 61,              // Key: F4
    KEY_F5 = 62,              // Key: F5
    KEY_F6 = 63,              // Key: F6
    KEY_F7 = 64,              // Key: F7
    KEY_F8 = 65,              // Key: F8
    KEY_F9 = 66,              // Key: F9
    KEY_F10 = 67,             // Key: F10
    KEY_F11 = 68,             // Key: F11
    KEY_F12 = 69,             // Key: F12
    KEY_LEFT_SHIFT = 225,     // Key: Shift left
    KEY_LEFT_CONTROL = 224,   // Key: Control left
    KEY_LEFT_ALT = 226,       // Key: Alt left
    KEY_LEFT_SUPER = 227,     // Key: Super left
    KEY_RIGHT_SHIFT = 229,    // Key: Shift right
    KEY_RIGHT_CONTROL = 228,  // Key: Control right
    KEY_RIGHT_ALT = 230,      // Key: Alt right
    KEY_RIGHT_SUPER = 231,    // Key: Super right
    KEY_KB_MENU = 232,        // Key: KB menu
    // Keypad keys
    KEY_KP_0 = 320,         // Key: Keypad 0
    KEY_KP_1 = 321,         // Key: Keypad 1
    KEY_KP_2 = 322,         // Key: Keypad 2
    KEY_KP_3 = 323,         // Key: Keypad 3
    KEY_KP_4 = 324,         // Key: Keypad 4
    KEY_KP_5 = 325,         // Key: Keypad 5
    KEY_KP_6 = 326,         // Key: Keypad 6
    KEY_KP_7 = 327,         // Key: Keypad 7
    KEY_KP_8 = 328,         // Key: Keypad 8
    KEY_KP_9 = 329,         // Key: Keypad 9
    KEY_KP_DECIMAL = 330,   // Key: Keypad .
    KEY_KP_DIVIDE = 331,    // Key: Keypad /
    KEY_KP_MULTIPLY = 332,  // Key: Keypad *
    KEY_KP_SUBTRACT = 333,  // Key: Keypad -
    KEY_KP_ADD = 334,       // Key: Keypad +
    KEY_KP_ENTER = 335,     // Key: Keypad Enter
    KEY_KP_EQUAL = 336,     // Key: Keypad =
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
                           const alinalib_Vector2 p1,
                           const alinalib_Vector2 p2,
                           const alinalib_Color color);

    // ────────────────────────────────────────────────────────────────
    //                             TIME
    // ────────────────────────────────────────────────────────────────

    // Load font
    alinalib_TTFFont *alinalib_loadFont(const char *filePath, int size);
    // Dispose font
    void alinalib_disposeFont(alinalib_TTFFont *font);
    // Set font size
    void alinalib_setFontSize(alinalib_TTFFont *font, int ptsize);
    // Mesure text size
    alinalib_Vector2 alinalib_measureText(const char *text,
                                          alinalib_TTFFont *font);
    // Draw text by using default font
    void alinalib_drawText(alinalib_Context *ctx,
                           const char *text,
                           const alinalib_Vector2 position,
                           const alinalib_Color color);
    // Draw custom text using specified font, angle, glow effect
    void alinalib_drawCustomText(alinalib_Context *ctx,
                                 alinalib_TTFFont *font,
                                 const char *text,
                                 const alinalib_Vector2 position,
                                 const alinalib_Vector2 origin,
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
    int alinalib_inputIsKeyDown(alinalib_Context *ctx,
                                const alinalib_Keycode key);
    int alinalib_inputIsKeyUp(alinalib_Context *ctx,
                              const alinalib_Keycode key);
    int alinalib_inputIsKeyPressed(alinalib_Context *ctx,
                                   const alinalib_Keycode key);
    // Get mouse states
    alinalib_Vector2 alinalib_inputGetMousePosition(alinalib_Context *ctx);
    int alinalib_inputIsMouseButtonDown(alinalib_Context *ctx,
                                        const alinalib_MouseButton button);
    int alinalib_inputIsMouseButtonUp(alinalib_Context *ctx,
                                      const alinalib_MouseButton button);
    int alinalib_inputIsMouseButtonPressed(alinalib_Context *ctx,
                                           const alinalib_MouseButton button);

#if defined(__cplusplus)
}
#endif

#endif  // !ALINALIB_H
