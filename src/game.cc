#include "game.h"
using namespace std;

  Game::Game(Board& board):board(board)
  {
    init(board);
    display = new Display(color);
  }

  void Game::init(Board& board)
  {
    state = RUNNING_STATE;
    playerTurn = PLAYER_X;
    board.init();
  }

  int Game::get_state()
  {
    return state;
  }

  void Game::set_state(int newState)
  {
    state = newState;
  }

  bool Game::check_player_won(symbol_t symbol)
  {
    board_t grid = board.get_board();
    int lineCount = 0;
    int columnCount = 0;
    int diag1Count = 0;
    int diag2Count = 0;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      for (int j = 0; j < BOARD_SIZE; ++j)
      {
          if (grid[i][j] == symbol)
            ++lineCount;
          if (grid[j][i] == symbol)
            ++columnCount;
      }
      if (lineCount >= BOARD_SIZE || columnCount >= BOARD_SIZE)
        return true;
      lineCount = 0;
      columnCount = 0;
      if (grid[i][i] == symbol)
        diag1Count++;
      if (grid[i][BOARD_SIZE -1 - i] == symbol)
        diag2Count++;
    }
    return (diag1Count >= BOARD_SIZE || diag2Count >= BOARD_SIZE ? true : false);
  }

  void Game::update_state(Board board)
  {
    if (check_player_won(cross))
      state = PLAYER_X_WON_STATE;
    else if (check_player_won(circle))
      state = PLAYER_O_WON_STATE;
    else if (board.count_cells(empty))
      state = TIE_STATE;
  }

  symbol_t Game::get_symbol()
  {
    if (playerTurn == PLAYER_X)
      return cross;
    else
      return circle;
  }

  void Game::switch_player()
  {
    if (playerTurn == PLAYER_X)
      playerTurn = PLAYER_0;
    else
      playerTurn = PLAYER_X;
  }

  void Game::update_game(SDL_Renderer *renderer)
  {
    switch (state)
    {
      case RUNNING_STATE:
        display->playinggame(renderer, board);
        break;
      case PLAYER_X_WON_STATE:
        display->overgame(renderer, board, color.get_color(PLAYER_X_COLOR));
        break;
      case PLAYER_O_WON_STATE:
        display->overgame(renderer, board, color.get_color(PLAYER_O_COLOR));
        break;
      case TIE_STATE:
        display->overgame(renderer, board, color.get_color(TIE_COLOR));
      default : {}
    }
  }
