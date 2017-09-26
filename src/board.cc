/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:39:01 by rfulop            #+#    #+#             */
/*   Updated: 2017/09/26 22:39:02 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
using namespace std;

  Board::Board()
  {
    init();
  }

  void Board::init()
  {
    for (auto &line : board)
      for (auto &column : line)
        column = empty;
  }

  board_t Board::get_board()
  {
    return board;
  }

  void Board::set_case(int i, int j, symbol_t symbol)
  {
    board[i][j] = symbol;
  }

  bool Board::count_cells(symbol_t cell)
  {
    int count = 0;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      for (int j = 0; j < BOARD_SIZE; ++j)
      {
        if (board[i][j] == cell)
          ++count;
      }
    }
    return (!count ? true : false);
  }

  void Board::click_on_board(int line, int column, symbol_t symbol)
  {
    if (board[line][column] == empty)
      board[line][column] = symbol;
  }
