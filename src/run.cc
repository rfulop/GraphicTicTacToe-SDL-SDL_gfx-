/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.cc                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:39:27 by rfulop            #+#    #+#             */
/*   Updated: 2018/01/15 17:59:22 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
using namespace std;
using namespace this_thread;
using namespace chrono;

void run_game(SDL_Renderer *renderer)
{
  Board board;
  Game game(board);
  Ai ai;

  SDL_Event event;
  while (game.get_state() != QUIT_STATE)
  {
    if (game.get_symbol() == cross)
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
    }
    else if (game.get_state() == RUNNING_STATE)
      ai.play(game, board, DIFFICULTY);
    else
    {
      sleep_until(system_clock::now() + seconds(1));
      game.init(board);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    game.update_game(renderer);
    SDL_RenderPresent(renderer);
  }
}
