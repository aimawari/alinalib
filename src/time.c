#include "alinalib.h"

// Initializes time management variables
void alinalib__timeInit(alinalib_Time *time)
{
    time->frameStart = 0;
    time->frameTime = 0;
    time->deltaTime = 0.f;
    time->frameCount = 0;
    time->currentFps = 0.f;
    time->fpsStartTime = SDL_GetTicks();
    time->targetFps = 60;
}

// Starts the timer for the current frame
void alinalib__timeStartFrame(alinalib_Time *time)
{
    Uint32 currentTime = SDL_GetTicks();
    time->deltaTime = (currentTime - time->frameStart) / 1000.f;
    time->frameStart = currentTime;
}

// Ends the timer for the current frame and updates time data
void alinalib__timeEndFrame(alinalib_Time *time)
{
    // Frame time calculation
    time->frameTime = SDL_GetTicks() - time->frameStart;

    // Calculate the delay time to cap the frame rate
    int frameDuration =
        1000 / time->targetFps;  // Target duration per frame in milliseconds
    if (time->frameTime < frameDuration)
    {
        SDL_Delay(frameDuration - time->frameTime);
    }

    // Update frame count
    time->frameCount++;

    // Calculate FPS every second
    if (SDL_GetTicks() - time->fpsStartTime >= 1000)
    {
        time->currentFps = time->frameCount;  // Set FPS
        time->frameCount = 0;                 // Reset frame count
        time->fpsStartTime =
            SDL_GetTicks();  // Reset the start time for FPS calculation
    }
}

// Sets the target FPS for rendering
void alinalib_timeSetTargetFps(alinalib_Time *time, int target_fps)
{
    time->targetFps = target_fps;
}
