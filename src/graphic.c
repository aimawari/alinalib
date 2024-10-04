#include "alinalib.h"

// Clears the screen with a specified color
void alinalib_clear(alinalib_Context *ctx, alinalib_Color color)
{
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(ctx->renderer);
}

// Draws an outlined rectangle
void alinalib_drawRectangle(alinalib_Context *ctx,
                            alinalib_Rect rect,
                            alinalib_Color color)
{
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(ctx->renderer, &rect);
}

// Draws a filled rectangle
void alinalib_drawFilledRectangle(alinalib_Context *ctx,
                                  alinalib_Rect rect,
                                  alinalib_Color color)
{
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(ctx->renderer, &rect);
}

// Draws a line between two points
void alinalib_drawLine(alinalib_Context *ctx,
                       alinalib_Point p1,
                       alinalib_Point p2,
                       alinalib_Color color)
{
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(ctx->renderer, p1.x, p1.y, p2.x, p2.y);
}
