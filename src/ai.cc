/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.cc                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:38:50 by rfulop            #+#    #+#             */
/*   Updated: 2018/01/15 17:28:25 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
using namespace std;
using namespace this_thread;
using namespace chrono;

int Ai::score_pawns(int pawns, int player)
{
  switch (pawns)
  {
    case 1:
      return 10 * player;
    case 2:
      return 30 * player;
    default:
      return 0;
  }
}

int Ai::eval(Game& game, Board& board)
{
  int score = 0;
  int pawns;
  int player;
  board_t tab = board.get_board();

  if (game.get_state() != RUNNING_STATE)
  {
    if (game.get_winner() == currentPlayer)
      return 1000 - count_pawns(board);
    else if (game.get_winner() == empty)
      return 0;
    else
      return -1000 + count_pawns(board);
  }

  pawns = 0;
  player = 0;
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    if (tab[i][i] != empty)
    {
      ++pawns;
      if (currentPlayer == tab[i][i])
        ++player;
      else
        --player;
    }
  }
  score += score_pawns(pawns, player);

  pawns = 0;
  player = 0;
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    if (tab[i][BOARD_SIZE -1 -i] != empty)
    {
      ++pawns;
      if (currentPlayer == tab[i][BOARD_SIZE -1 -i])
        ++player;
      else
        --player;
    }
  }
  score += score_pawns(pawns, player);

  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    pawns = 0;
    player = 0;
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      if (tab[i][j] != empty)
      {
        ++pawns;
        if (currentPlayer == tab[i][j])
          ++player;
        else
          --player;
      }
    }
    score += score_pawns(pawns, player);
  }
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    pawns = 0;
    player = 0;
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      if (tab[j][i] != empty)
      {
        ++pawns;
        if (currentPlayer == tab[j][i])
          ++player;
        else
          --player;
      }
    }
    score += score_pawns(pawns, player);
  }
  return score;
}

int Ai::count_pawns(Board& board)
{
  int pawns = 0;
  board_t tab = board.get_board();

  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      if (tab[i][j] != empty)
        ++pawns;
  return pawns;
}

void Ai::play(Game &game, Board &board, int depth)
{
  int tmp;
  int max = minEval;
  int maxI = -1;
  int maxJ = -1;
  board_t tab = board.get_board();

  currentPlayer = game.get_symbol();
  if (!depth || game.get_state() != RUNNING_STATE)
    return ;
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      if (tab[i][j] == empty)
      {
        game.play_move(board, i, j);
        tmp = calc_min(game, board, depth - 1);
        if (tmp > max || ((tmp == max) && (std::rand()%2 == 0)))
        {
          max = tmp;
          maxI = i;
          maxJ = j;
        }
        game.cancel_move(board, i, j);
      }
    }
  }
  sleep_until(system_clock::now() + seconds(1));
  game.play_move(board, maxI, maxJ);
}

int Ai::calc_min(Game &game, Board &board, int depth)
{
  int tmp;
  int min = maxEval;
  board_t tab = board.get_board();

  if (!depth || game.get_state() != RUNNING_STATE)
    return eval(game, board);
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      if (tab[i][j] == empty)
      {
            game.play_move(board, i, j);
            tmp = calc_max(game, board, depth -1);
            if (tmp < min || ((tmp == min) && (std::rand()%2 == 0)))
              min = tmp;
            game.cancel_move(board, i, j);
      }
    }
  }
  return min;
}

int Ai::calc_max(Game &game, Board &board, int depth)
{
  int tmp;
  int max = minEval;
  board_t tab = board.get_board();

  if (!depth || game.get_state() != RUNNING_STATE)
    return eval(game, board);
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      if (tab[i][j] == empty)
      {
            game.play_move(board, i, j);
            tmp = calc_min(game, board, depth -1);
            if (tmp > max || ((tmp == max) && (std::rand()%2 == 0)))
              max = tmp;
            game.cancel_move(board, i, j);
      }
    }
  }
  return max;
}
