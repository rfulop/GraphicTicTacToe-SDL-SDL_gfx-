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

int Ai::eval(Game& game)
{
  int score = 0;
  int pawns;
  int player;
  board_t tab = game.board.get_board();

  if (game->state != RUNNING_STATE)
  {
    if (game->state == PLAYER_X_WON_STATE)
      return -1000 + count_pawns(game);
    else if (game->state == PLAYER_O_WON_STATE)
      return 1000 - count_pawns(game);
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
      if (game.get_player_turn() == tab[i][i])
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
      if (game.get_player_turn() == tab[i][BOARD_SIZE -1 -i])
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
        if (game.get_player_turn() == tab[i][j])
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
        if (game.get_player_turn() == tab[j][i])
          ++player;
        else
          --player;
      }
    }
    score += score_pawns(pawns, player);
  }
  return score;
}

int Ai::count_pawns(Game &game)
{
  int pawns = 0;
  board_t tab = game.board.get_board();

  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      if (tab[i][j] != empty)
        ++pawns;
  return pawns;
}

void Ai::calc_move(Game &game, int depth)
{
}
