#include "game.h"
using namespace std;



void run_game(SDL_Renderer *renderer)
{
  Board board;
  Game game(board);

  SDL_Event event;
  while (game.get_state() != QUIT_STATE)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          game.set_state(QUIT_STATE);
          break;
        case SDL_MOUSEBUTTONDOWN:
        {
          if (game.get_state() == RUNNING_STATE)
          {
            board.click_on_board(event.button.y / CELL_HEIGHT, event.button.x / CELL_WIDTH, game.get_symbol());
            game.switch_player();
            game.update_state(board);
          }
          else
            game.init(board);
          break;
        }
        default: {}
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    game.update_game(renderer);
    SDL_RenderPresent(renderer);
  }
}
