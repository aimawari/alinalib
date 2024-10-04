#include "alinalib.h"

int main() {
  alinalib_context *ctx = alinalib_init_context("Example alinalib", 240, 160);

  if (!ctx) {
    alinalib_cleanup_context(ctx);
    return -1;
  }

  while (!ctx->should_close) {
    alinalib_start_frame(ctx);

    alinalib_clear(ctx, BLACK);

    alinalib_draw_line(
        ctx, (alinalib_point){0, ctx->window_height - 20},
        (alinalib_point){ctx->window_width, ctx->window_height - 20}, GREEN);

    int rect_size = 16;
    alinalib_draw_filled_rectangle(
        ctx,
        (alinalib_rect){(ctx->window_width - 16) / 2,
                        (ctx->window_height - 16) / 2, rect_size, rect_size},
        RED);

    printf("dt: %.2f\n", ctx->time.delta_time);
    printf("FPS: %.2f\n", ctx->time.current_fps);

    alinalib_end_frame(ctx);
  }

  alinalib_cleanup_context(ctx);

  return 0;
}
