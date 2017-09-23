#include "game.h"
using namespace std;

void sdl_print_error(int errorNum)
{
  switch (errorNum)
  {
    case INIT_ERROR:
      cerr << "Could not initilize sdl2: ";
      break;
    case WINDOW_ERROR:
      cerr << "SDL_CreateWindow Error: ";
      break;
    case RENDERER_ERROR:
      cerr << "SDL_CreateRenderer Error: ";
      break;
    default: {}
  }
  cerr << SDL_GetError() << endl;
  exit (EXIT_FAILURE);
}
