#include "alinalib.h"
#include <SDL_render.h>

void alinalib_clear(alinalib_context *ctx, alinalib_color color) {
  SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(ctx->renderer);
}

void alinalib_draw_rectangle(alinalib_context *ctx, alinalib_rect rect,
                             alinalib_color color) {
  SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(ctx->renderer, &rect);
}

void alinalib_draw_filled_rectangle(alinalib_context *ctx, alinalib_rect rect,
                                    alinalib_color color) {
  SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(ctx->renderer, &rect);
}

void alinalib_draw_line(alinalib_context *ctx, alinalib_point p1,
                        alinalib_point p2, alinalib_color color) {
  SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(ctx->renderer, p1.x, p1.y, p2.x, p2.y);
}
