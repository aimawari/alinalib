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
    KEY_NULL = 0,
    // Alphanumeric keys
    KEY_APOSTROPHE = 52,     // '
    KEY_COMMA = 44,          // ,
    KEY_MINUS = 45,          // -
    KEY_PERIOD = 46,         // .
    KEY_SLASH = 47,          // /
    KEY_ZERO = 48,           // 0
    KEY_ONE = 49,            // 1
    KEY_TWO = 50,            // 2
    KEY_THREE = 51,          // 3
    KEY_FOUR = 52,           // 4
    KEY_FIVE = 53,           // 5
    KEY_SIX = 54,            // 6
    KEY_SEVEN = 55,          // 7
    KEY_EIGHT = 56,          // 8
    KEY_NINE = 57,           // 9
    KEY_SEMICOLON = 59,      // ;
    KEY_EQUAL = 61,          // =
    KEY_A = 65,              // A
    KEY_B = 66,              // B
    KEY_C = 67,              // C
    KEY_D = 68,              // D
    KEY_E = 69,              // E
    KEY_F = 70,              // F
    KEY_G = 71,              // G
    KEY_H = 72,              // H
    KEY_I = 73,              // I
    KEY_J = 74,              // J
    KEY_K = 75,              // K
    KEY_L = 76,              // L
    KEY_M = 77,              // M
    KEY_N = 78,              // N
    KEY_O = 79,              // O
    KEY_P = 80,              // P
    KEY_Q = 81,              // Q
    KEY_R = 82,              // R
    KEY_S = 83,              // S
    KEY_T = 84,              // T
    KEY_U = 85,              // U
    KEY_V = 86,              // V
    KEY_W = 87,              // W
    KEY_X = 88,              // X
    KEY_Y = 89,              // Y
    KEY_Z = 90,              // Z
    KEY_LEFT_BRACKET = 91,   // [
    KEY_BACKSLASH = 92,      // '\'
    KEY_RIGHT_BRACKET = 93,  // ]
    KEY_GRAVE = 96,          // `
    // Function keys
    KEY_SPACE = 32,           // Space
    KEY_ESCAPE = 27,          // Esc
    KEY_ENTER = 13,           // Enter
    KEY_TAB = 9,              // Tab
    KEY_BACKSPACE = 8,        // Backspace
    KEY_INSERT = 45,          // Ins
    KEY_DELETE = 46,          // Del
    KEY_RIGHT = 39,           // Cursor right
    KEY_LEFT = 37,            // Cursor left
    KEY_DOWN = 40,            // Cursor down
    KEY_UP = 38,              // Cursor up
    KEY_PAGE_UP = 33,         // Page up
    KEY_PAGE_DOWN = 34,       // Page down
    KEY_HOME = 36,            // Home
    KEY_END = 35,             // End
    KEY_CAPS_LOCK = 20,       // Caps lock
    KEY_SCROLL_LOCK = 145,    // Scroll lock
    KEY_NUM_LOCK = 144,       // Num lock
    KEY_PRINT_SCREEN = 42,    // Print screen
    KEY_PAUSE = 19,           // Pause
    KEY_F1 = 112,             // F1
    KEY_F2 = 113,             // F2
    KEY_F3 = 114,             // F3
    KEY_F4 = 115,             // F4
    KEY_F5 = 116,             // F5
    KEY_F6 = 117,             // F6
    KEY_F7 = 118,             // F7
    KEY_F8 = 119,             // F8
    KEY_F9 = 120,             // F9
    KEY_F10 = 121,            // F10
    KEY_F11 = 122,            // F11
    KEY_F12 = 123,            // F12
    KEY_LEFT_SHIFT = 160,     // Shift left
    KEY_LEFT_CONTROL = 162,   // Control left
    KEY_LEFT_ALT = 164,       // Alt left
    KEY_LEFT_SUPER = 91,      // Super left
    KEY_RIGHT_SHIFT = 161,    // Shift right
    KEY_RIGHT_CONTROL = 163,  // Control right
    KEY_RIGHT_ALT = 165,      // Alt right
    KEY_RIGHT_SUPER = 92,     // Super right
    KEY_KB_MENU = 93,         // KB menu
    // Keypad keys
    KEY_KP_0 = 96,          // Keypad 0
    KEY_KP_1 = 97,          // Keypad 1
    KEY_KP_2 = 98,          // Keypad 2
    KEY_KP_3 = 99,          // Keypad 3
    KEY_KP_4 = 100,         // Keypad 4
    KEY_KP_5 = 101,         // Keypad 5
    KEY_KP_6 = 102,         // Keypad 6
    KEY_KP_7 = 103,         // Keypad 7
    KEY_KP_8 = 104,         // Keypad 8
    KEY_KP_9 = 105,         // Keypad 9
    KEY_KP_DECIMAL = 110,   // Keypad .
    KEY_KP_DIVIDE = 111,    // Keypad /
    KEY_KP_MULTIPLY = 106,  // Keypad *
    KEY_KP_SUBTRACT = 109,  // Keypad -
    KEY_KP_ADD = 107,       // Keypad +
    KEY_KP_ENTER = 104,     // Keypad Enter
    KEY_KP_EQUAL = 103,     // Keypad =
    // Android key buttons
    KEY_MENU = 82,        // Android menu button
    KEY_VOLUME_UP = 24,   // Android volume up button
    KEY_VOLUME_DOWN = 25  // Android volume down button
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
