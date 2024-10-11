#include "alinalib.h"

extern void alinalib__timeInit(alinalib_Context *ctx);
extern void alinalib__timeStartFrame(alinalib_Context *ctx);
extern void alinalib__timeEndFrame(alinalib_Context *ctx);
extern TTF_Font *alinalib__loadDefuaultFont();

extern void alinalib__inputInit(alinalib_Context *ctx);
extern void alinalib__inputStartFrame(alinalib_Context *ctx);
extern void alinalib__inputEndFrame(alinalib_Context *ctx);
extern void alinalib__inputHandler(alinalib_Context *ctx, SDL_Event *event);

// Initializes the app context with a window and renderer
alinalib_Context *alinalib_initContext(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialized! Error: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() < 0)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        return NULL;
    }

    alinalib_Context *ctx =
        (alinalib_Context *)malloc(sizeof(alinalib_Context));

    if (!ctx)
    {
        printf("Failed to allocate memory for context\n");
        return NULL;
    }

    ctx->window = SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   width,
                                   height,
                                   SDL_WINDOW_SHOWN);
    if (!ctx->window)
    {
        printf("Failed to create window! Error: %s\n", SDL_GetError());
        free(ctx);
        return NULL;
    }

    ctx->renderer =
        SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
    if (!ctx->renderer)
    {
        printf("Failed to create renderer! Error: %s\n", SDL_GetError());
        free(ctx);
        return NULL;
    }

    ctx->defaultFont = alinalib__loadDefuaultFont();

    ctx->shouldClose = 0;
    ctx->windowWidth = width;
    ctx->windowHeight = height;

    alinalib__timeInit(ctx);
    alinalib__inputInit(ctx);

    return ctx;
}

// Cleans up the resources used by the app context
void alinalib_cleanupContext(alinalib_Context *ctx)
{
    if (ctx->renderer)
    {
        SDL_DestroyRenderer(ctx->renderer);
    }

    if (ctx->window)
    {
        SDL_DestroyWindow(ctx->window);
    }

    if (ctx->defaultFont)
    {
        alinalib_disposeFont(ctx->defaultFont);
    }

    free(ctx);
    TTF_Quit();
    SDL_Quit();
}

// Starts a new frame for rendering
void alinalib_startFrame(alinalib_Context *ctx)
{
    alinalib__timeStartFrame(ctx);
}

// Ends the current frame and does any necessary updates
void alinalib_endFrame(alinalib_Context *ctx)
{
    SDL_RenderPresent(ctx->renderer);

    alinalib__inputStartFrame(ctx);

    // Poll event
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            ctx->shouldClose = 1;
        }

        alinalib__inputHandler(ctx, &event);
    }

    alinalib__inputEndFrame(ctx);
    alinalib__timeEndFrame(ctx);
}
