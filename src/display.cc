/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:39:09 by rfulop            #+#    #+#             */
/*   Updated: 2017/09/26 22:39:10 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
using namespace std;

  Display::Display(Color& color):color(color) {}

  void Display::grid(SDL_Renderer *renderer, const SDL_Color& color)
  {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = 1; i < BOARD_SIZE; ++i)
    {
      SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT);
      SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCREEN_WIDTH, i * CELL_HEIGHT);
    }
  }

  void Display::p_cross(SDL_Renderer *renderer, int line, int column, const SDL_Color& color)
  {
    const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 + line * CELL_HEIGHT;

      thickLineRGBA(renderer, centerX - half_box_side, centerY - half_box_side, centerX + half_box_side,
                    centerY + half_box_side, 10, color.r, color.g, color.b, color.a);
      thickLineRGBA(renderer, centerX + half_box_side, centerY - half_box_side, centerX - half_box_side,
                    centerY + half_box_side, 10, color.r, color.g, color.b, color.a);
  }

  void Display::p_circle(SDL_Renderer *renderer, int line, int column, const SDL_Color& color)
  {
    const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 + line * CELL_HEIGHT;

    filledCircleRGBA(renderer, centerX, centerY, half_box_side + 5, color.r, color.g,
                    color.b, color.a);
    filledCircleRGBA(renderer, centerX, centerY, half_box_side - 5, 0, 0, 0, 255);
  }


  void Display::overgame(SDL_Renderer *renderer, Board board, const SDL_Color& col)
  {
    board_t tab = board.get_board();

    grid(renderer, col);
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      for (int j = 0; j < BOARD_SIZE; ++j)
      {
        if (tab[i][j] == cross)
          p_cross(renderer, i, j, col);
        if (tab[i][j] == circle)
          p_circle(renderer, i, j, col);
      }
    }
  }

  void Display::playinggame(SDL_Renderer *renderer, Board board)
  {
    board_t tab = board.get_board();

    grid(renderer, color.get_color(GRID_COLOR));
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      for (int j = 0; j < BOARD_SIZE; ++j)
      {
        if (tab[i][j] == cross)
          p_cross(renderer, i, j, color.get_color(PLAYER_X_COLOR));
        if (tab[i][j] == circle)
          p_circle(renderer, i, j, color.get_color(PLAYER_O_COLOR));
      }
    }
  }
