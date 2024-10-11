#include "SDL_events.h"
#include "alinalib.h"

typedef struct alinalib__KeyboardInput
{
    int exitKey;
    int keys[MAX_KEYBOARD_KEYS];
    int prevKeys[MAX_KEYBOARD_KEYS];
    int keysPressed[MAX_KEYBOARD_KEYS];
} alinalib_KeyboardInput;

typedef struct alinalib__MouseInput
{
    alinalib_Point mousePosition;
    int mouseButton[MAX_MOUSE_BUTTON];
    int prevMouseButton[MAX_MOUSE_BUTTON];
    int mouseButtonPressed[MAX_MOUSE_BUTTON];
} alinalib_MouseInput;

typedef struct alinalib__Input
{
    alinalib_KeyboardInput keyboard;
    alinalib_MouseInput mouse;
} alinalib_Input;

// Initializes time management variables
void alinalib__inputInit(alinalib_Context *ctx)
{
    ctx->input = (alinalib_Input *)malloc(sizeof(alinalib_Input));
    if (ctx->input == NULL)
    {
        printf("Memory allocation failed for alinalib_Input\n");
    }

    // Init keyboard
    ctx->input->keyboard.exitKey = KEY_ESCAPE;  // Set default exit key
    memset(ctx->input->keyboard.keys, 0, sizeof(ctx->input->keyboard.keys));
}

void alinalib__inputStartFrame(alinalib_Context *ctx)
{
    memset(ctx->input->keyboard.keysPressed,
           0,
           sizeof(ctx->input->keyboard.keysPressed));
    memset(ctx->input->mouse.mouseButton,
           0,
           sizeof(ctx->input->mouse.mouseButton));
}

void alinalib__inputEndFrame(alinalib_Context *ctx)
{
    memcpy(ctx->input->keyboard.prevKeys,
           ctx->input->keyboard.keys,
           sizeof(ctx->input->keyboard.keys));
    memcpy(ctx->input->mouse.prevMouseButton,
           ctx->input->mouse.mouseButton,
           sizeof(ctx->input->mouse.mouseButton));
}

void alinalib__inputHandler(alinalib_Context *ctx, SDL_Event *event)
{
    // Set exit key
    if (ctx->input->keyboard.keys[ctx->input->keyboard.exitKey])
    {
        ctx->shouldClose = 1;
    }

    // Keyboard handler
    if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
    {
        if (event->type == SDL_KEYDOWN)
        {
            ctx->input->keyboard.keys[event->key.keysym.scancode] = 1;

            if (!event->key.repeat)
            {
                ctx->input->keyboard.keysPressed[event->key.keysym.scancode] =
                    1;
            }
        }
        if (event->type == SDL_KEYUP)
        {
            ctx->input->keyboard.keys[event->key.keysym.scancode] = 0;
        }
    }

    // Mouse handler
    if (event->type == SDL_MOUSEMOTION)
    {
        ctx->input->mouse.mousePosition =
            (alinalib_Point){event->motion.x, event->motion.y};
    }
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
    {
        if (event->type == SDL_MOUSEBUTTONDOWN)
        {
            ctx->input->mouse.mouseButton[event->button.button] = 1;

            if (!event->key.repeat)
            {
                ctx->input->mouse.mouseButtonPressed[event->button.button] = 1;
            }
        }
        if (event->type == SDL_MOUSEBUTTONUP)
        {
            ctx->input->mouse.mouseButton[event->button.button] = 0;
        }
    }
}

int alinalib_inputIsKeyDown(alinalib_Context *ctx, alinalib_Keycode key)
{
    return ctx->input->keyboard.keys[key];
}

int alinalib_inputIsKeyUp(alinalib_Context *ctx, alinalib_Keycode key)
{
    return ctx->input->keyboard.keysPressed[key] &&
           !ctx->input->keyboard.keys[key];
}

int alinalib_inputIsKeyPressed(alinalib_Context *ctx, alinalib_Keycode key)
{
    return ctx->input->keyboard.keysPressed[key];
}

alinalib_Point alinalib_inputGetMousePosition(alinalib_Context *ctx)
{
    return ctx->input->mouse.mousePosition;
}

int alinalib_inputIsMouseButtonDown(alinalib_Context *ctx,
                                    alinalib_MouseButton button)
{
    return ctx->input->mouse.mouseButton[button];
}

int alinalib_inputIsMouseButtonUp(alinalib_Context *ctx,
                                  alinalib_MouseButton button)
{
    return ctx->input->mouse.mouseButtonPressed[button] &&
           !ctx->input->mouse.mouseButton[button];
}

int alinalib_inputIsMouseButtonPressed(alinalib_Context *ctx,
                                       alinalib_MouseButton button)
{
    return ctx->input->mouse.mouseButtonPressed[button];
}
