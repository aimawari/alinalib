#include "alinalib.h"

extern void alinalib__timeInit(alinalib_Time *time);
extern void alinalib__timeStartFrame(alinalib_Time *time);
extern void alinalib__timeEndFrame(alinalib_Time *time);

// Initializes the app context with a window and renderer
alinalib_Context *alinalib_initContext(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialized! Error: %s\n", SDL_GetError());
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

    ctx->shouldClose = 0;
    ctx->windowWidth = width;
    ctx->windowHeight = height;

    alinalib__timeInit(&ctx->time);

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
    free(ctx);
    SDL_Quit();
}

// Starts a new frame for rendering
void alinalib_startFrame(alinalib_Context *ctx)
{
    alinalib__timeStartFrame(&ctx->time);
}

// Ends the current frame and does any necessary updates
void alinalib_endFrame(alinalib_Context *ctx)
{
    SDL_RenderPresent(ctx->renderer);

    // Poll event
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            ctx->shouldClose = 1;
        }
        if (event.type == SDL_KEYDOWN)
        {
            ctx->shouldClose = 1;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            ctx->shouldClose = 1;
        }
    }

    alinalib__timeEndFrame(&ctx->time);
}
