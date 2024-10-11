#include "alinalib.h"

// ╔══════════════════════════════════════════════════════════╗
// ║                          TYPES                            ║
// ╚══════════════════════════════════════════════════════════╝

// Struct for managing time during frame rendering
typedef struct alinalib__Time
{
    Uint32 frameStart;  // Time when the current frame started
    Uint32 frameTime;   // Time taken to render the current frame (in ms)

    // FPS calculation variables
    int frameCount;       // Number of frames in the last second
    Uint32 fpsStartTime;  // Time when FPS was last calculated

    // Frame rate control
    int targetFps;  // Desired frames per second
} alinalib_Time;

// Initializes time management variables
void alinalib__timeInit(alinalib_Context *ctx)
{
    ctx->deltaTime = 0.f;
    ctx->currentFps = 0.f;

    ctx->time = (alinalib_Time *)malloc(sizeof(alinalib_Time));
    if (ctx->time == NULL)
    {
        printf("Memory allocation failed for my_Time\n");
    }

    ctx->time->frameStart = 0;
    ctx->time->frameTime = 0;
    ctx->time->frameCount = 0;
    ctx->time->fpsStartTime = SDL_GetTicks();
    ctx->time->targetFps = 60;
}

// Starts the timer for the current frame
void alinalib__timeStartFrame(alinalib_Context *ctx)
{
    Uint32 currentTime = SDL_GetTicks();
    ctx->deltaTime = (currentTime - ctx->time->frameStart) / 1000.f;
    ctx->time->frameStart = currentTime;
}

// Ends the timer for the current frame and updates time data
void alinalib__timeEndFrame(alinalib_Context *ctx)
{
    // Frame time calculation
    ctx->time->frameTime = SDL_GetTicks() - ctx->time->frameStart;

    // Calculate the delay time to cap the frame rate
    int frameDuration =
        1000 /
        ctx->time->targetFps;  // Target duration per frame in milliseconds
    if (ctx->time->frameTime < frameDuration)
    {
        SDL_Delay(frameDuration - ctx->time->frameTime);
    }

    // Update frame count
    ctx->time->frameCount++;

    // Calculate FPS every second
    if (SDL_GetTicks() - ctx->time->fpsStartTime >= 1000)
    {
        ctx->currentFps = ctx->time->frameCount;  // Set FPS
        ctx->time->frameCount = 0;                // Reset frame count
        ctx->time->fpsStartTime =
            SDL_GetTicks();  // Reset the start time for FPS calculation
    }
}

// Sets the target FPS for rendering
void alinalib_timeSetTargetFps(alinalib_Context *ctx, int target_fps)
{
    ctx->time->targetFps = target_fps;
}
