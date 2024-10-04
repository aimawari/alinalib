#include "alinalib.h"

void alinalib_time_init(alinalib_time *time) {
  time->frame_start = 0;
  time->frame_time = 0;
  time->delta_time = 0.f;
  time->frame_count = 0;
  time->current_fps = 0.f;
  time->fps_start_time = SDL_GetTicks();
  time->target_fps = 60;
}

void alinalib_time_start_frame(alinalib_time *time) {
  Uint32 current_time = SDL_GetTicks();
  time->delta_time = (current_time - time->frame_start) / 1000.f;
  time->frame_start = current_time;
}

void alinalib_time_end_frame(alinalib_time *time) {
  // Frame time calculation
  time->frame_time = SDL_GetTicks() - time->frame_start;

  // Calculate the delay time to cap the frame rate
  int frame_duration =
      1000 / time->target_fps; // Target duration per frame in milliseconds
  if (time->frame_time < frame_duration) {
    SDL_Delay(frame_duration - time->frame_time);
  }

  // Update frame count
  time->frame_count++;

  // Calculate FPS every second
  if (SDL_GetTicks() - time->fps_start_time >= 1000) {
    time->current_fps = time->frame_count;    // Set FPS
    printf("FPS: %.2f\n", time->current_fps); // Print FPS
    time->frame_count = 0;                    // Reset frame count
    time->fps_start_time =
        SDL_GetTicks(); // Reset the start time for FPS calculation
  }
}

void alinalib_time_set_target_fps(alinalib_time *time, int target_fps) {
  time->target_fps = target_fps;
}
