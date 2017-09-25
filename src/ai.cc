#include "game.h"
using namespace std;

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
    if (game.get_state() == PLAYER_X_WON_STATE)
      return -1000 + count_pawns(board);
    else if (game.get_state() == PLAYER_O_WON_STATE)
      return 1000 - count_pawns(board);
    else
      return 0;
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

void Ai::calc_move(Game &game, Board &board, int depth)
{
  int tmp;
  int max = minEval;
  int maxI = -1;
  int maxJ = -1;
  board_t tab = board.get_board();

  currentPlayer = game.get_symbol();
  if (depth || game.get_state() == RUNNING_STATE)
  {
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      for (int j = 0; j < BOARD_SIZE; ++j)
      {
        if (tab[i][j] == empty)
        {
          board.click_on_board(i, j, currentPlayer);
          tmp = calc_min(game, board, depth - 1);
          if (tmp >= max)
          {
            max = tmp;
            maxI = i;
            maxJ = j;
          }
          board.set_case(i, j, empty);
        }
      }
    }
  }
  board.click_on_board(maxI, maxJ, currentPlayer);
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
            board.click_on_board(i, j, currentPlayer);
            tmp = calc_max(game, board, depth -1);
            if (tmp < min)
              min = tmp;
            board.set_case(i, j, empty);
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
            board.click_on_board(i, j, currentPlayer);
            tmp = calc_min(game, board, depth -1);
            if (tmp > max)
              max = tmp;
            board.set_case(i, j, empty);
      }
    }
  }
  return max;
}
