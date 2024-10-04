#include "alinalib.h"

alinalib_context *alinalib_init_context(const char *title, int width,
                                        int height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialized! Error: %s\n", SDL_GetError());
    return NULL;
  }

  alinalib_context *ctx = (alinalib_context *)malloc(sizeof(alinalib_context));

  if (!ctx) {
    printf("Failed to allocate memory for context\n");
    return NULL;
  }

  ctx->window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);
  if (!ctx->window) {
    printf("Failed to create window! Error: %s\n", SDL_GetError());
    free(ctx);
    return NULL;
  }

  ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
  if (!ctx->renderer) {
    printf("Failed to create renderer! Error: %s\n", SDL_GetError());
    free(ctx);
    return NULL;
  }

  ctx->should_close = 0;
  ctx->window_width = width;
  ctx->window_height = height;

  alinalib_time_init(&ctx->time);

  return ctx;
}

void alinalib_cleanup_context(alinalib_context *ctx) {
  if (ctx->renderer) {
    SDL_DestroyRenderer(ctx->renderer);
  }

  if (ctx->window) {
    SDL_DestroyWindow(ctx->window);
  }
  free(ctx);
  SDL_Quit();
}

void alinalib_start_frame(alinalib_context *ctx) {
  alinalib_time_start_frame(&ctx->time);
}

void alinalib_end_frame(alinalib_context *ctx) {
  SDL_RenderPresent(ctx->renderer);

  // Poll event
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      ctx->should_close = 1;
    }
    if (event.type == SDL_KEYDOWN) {
      ctx->should_close = 1;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      ctx->should_close = 1;
    }
  }

  alinalib_time_end_frame(&ctx->time);
}
