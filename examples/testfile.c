#include <stdio.h>

#include "alinalib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MOVE_SPEED 250

int main(int argc, char* argv[])
{
    alinalib_Context* ctx =
        alinalib_initContext("Example alinalib", WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!ctx)
    {
        alinalib_cleanupContext(ctx);
        return -1;
    }

    alinalib_Vector2 playerPos = {
        (float)(ctx->windowWidth - 16) / 2,
        (float)(ctx->windowHeight - 16) / 2,
    };

    while (!ctx->shouldClose)
    {
        alinalib_startFrame(ctx);

        alinalib_clear(ctx, BLACK);

        if (alinalib_inputIsKeyDown(ctx, KEY_LEFT))
        {
            playerPos.x -= MOVE_SPEED * ctx->deltaTime;
        }
        if (alinalib_inputIsKeyDown(ctx, KEY_RIGHT))
        {
            playerPos.x += MOVE_SPEED * ctx->deltaTime;
        }
        if (alinalib_inputIsKeyDown(ctx, KEY_UP))
        {
            playerPos.y -= MOVE_SPEED * ctx->deltaTime;
        }
        if (alinalib_inputIsKeyDown(ctx, KEY_DOWN))
        {
            playerPos.y += MOVE_SPEED * ctx->deltaTime;
        }

        alinalib_drawLine(
            ctx,
            (alinalib_Point){0, ctx->windowHeight - 20},
            (alinalib_Point){ctx->windowWidth, ctx->windowHeight - 20},
            GREEN);

        int rectSize = 16;
        alinalib_drawFilledRectangle(
            ctx,
            (alinalib_Rect){playerPos.x, playerPos.y, rectSize, rectSize},
            RED);

        const char* helloText = "Hello World!";

        alinalib_Point textSize =
            alinalib_measureText(helloText, ctx->defaultFont);

        char fpsText[50];
        snprintf(fpsText, sizeof(fpsText), "FPS: %.2f", ctx->currentFps);

        alinalib_Point fpsTextPosition = {ctx->windowWidth - textSize.x, 0};

        alinalib_drawText(ctx, fpsText, &fpsTextPosition, WHITE);

        alinalib_endFrame(ctx);
    }

    alinalib_cleanupContext(ctx);

    return 0;
}
