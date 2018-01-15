/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:39:23 by rfulop            #+#    #+#             */
/*   Updated: 2018/01/15 17:58:18 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
using namespace std;

int main(void)
{
  if (SDL_Init(SDL_INIT_VIDEO))
    sdl_print_error(INIT_ERROR);

  SDL_Window *window = SDL_CreateWindow("TicTacToe", 100, 100,
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
