#include "alinalib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[])
{
    alinalib_Context* ctx =
        alinalib_initContext("Example alinalib", WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!ctx)
    {
        alinalib_cleanupContext(ctx);
        return -1;
    }

    while (!ctx->shouldClose)
    {
        alinalib_startFrame(ctx);

        alinalib_clear(ctx, BLACK);

        alinalib_drawLine(
            ctx,
            (alinalib_Point){0, ctx->windowHeight - 20},
            (alinalib_Point){ctx->windowWidth, ctx->windowHeight - 20},
            GREEN);

        int rectSize = 16;
        alinalib_drawFilledRectangle(
            ctx,
            (alinalib_Rect){(ctx->windowWidth - 16) / 2,
                            (ctx->windowHeight - 16) / 2,
                            rectSize,
                            rectSize},
            RED);

        alinalib_drawText(ctx, "Hello World", (alinalib_Point){0, 0}, WHITE);

        printf("dt: %.2f\n", ctx->time.deltaTime);
        printf("FPS: %.2f\n", ctx->time.currentFps);

        alinalib_endFrame(ctx);
    }

    alinalib_cleanupContext(ctx);

    return 0;
}
