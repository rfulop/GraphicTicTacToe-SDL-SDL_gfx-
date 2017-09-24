#include "game.h"

const SDL_Color Color::get_color(int color)
{
  switch (color)
  {
    case GRID_COLOR:
      return grey;
    case PLAYER_X_COLOR:
      return red;
    case PLAYER_O_COLOR:
      return blue;
    case TIE_COLOR:
      return grey;
    default:
      return black;
  }
}
