#include <SDL.h>

#include "alinalib.h"

// Clears the screen with a specified color
void alinalib_clear(alinalib_Context *ctx, const alinalib_Color color)
{
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(ctx->renderer);
}

// Draws an outlined rectangle
void alinalib_drawRectangle(alinalib_Context *ctx,
                            const alinalib_Rect rect,
                            const alinalib_Color color)
{
    SDL_Rect sdlRect = {(int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h};

    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(ctx->renderer, &sdlRect);
}

// Draws a filled rectangle
void alinalib_drawFilledRectangle(alinalib_Context *ctx,
                                  const alinalib_Rect rect,
                                  const alinalib_Color color)
{
    SDL_Rect sdlRect = {(int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h};

    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(ctx->renderer, &sdlRect);
}

// Draws a line between two points
void alinalib_drawLine(alinalib_Context *ctx,
                       const alinalib_Vector2 p1,
                       const alinalib_Vector2 p2,
                       const alinalib_Color color)
{
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(ctx->renderer, p1.x, p1.y, p2.x, p2.y);
}
