#include "game.h"
using namespace std;

int main()
{
  cout << "empty = " << empty << endl;
  cout << "x = " << cross << endl;
  cout << "o = " << circle << endl;
  cout << "PLAYER_X = " << PLAYER_X << endl;
  cout << "PLAYER_O = " << PLAYER_O << endl;
  if (SDL_Init(SDL_INIT_VIDEO))
    sdl_print_error(INIT_ERROR);

  SDL_Window *window = SDL_CreateWindow("Morpion", 100, 100,
  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window)
    sdl_print_error(WINDOW_ERROR);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer)
  {
    SDL_DestroyWindow(window);
    sdl_print_error(RENDERER_ERROR);
  }

  run_game(renderer);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
