#include <SDL.h>
int main(int, char**) {
  SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
  SDL_Window* win = SDL_CreateWindow("My SDL App",
                                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     800, 600, SDL_WINDOW_SHOWN);
  bool running = true;
  while (running) {
    SDL_Event e; while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) running = false;
    SDL_Delay(16);
  }
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
