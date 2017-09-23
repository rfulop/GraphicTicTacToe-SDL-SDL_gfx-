#include "game.h"
using namespace std;

  Game::Game(Board& board):board(board)
  {
    init(board);
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

  void Game::display_grid(SDL_Renderer *renderer, const SDL_Color *color)
  {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    for (int i = 1; i < BOARD_SIZE; ++i)
    {
      SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT);
      SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCREEN_WIDTH, i * CELL_HEIGHT);
    }
  }


  void Game::display_cross(SDL_Renderer *renderer, int line, int column, const SDL_Color *color)
  {
    const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 + line * CELL_HEIGHT;

      thickLineRGBA(renderer, centerX - half_box_side, centerY - half_box_side, centerX + half_box_side,
                    centerY + half_box_side, 10, color->r, color->g, color->b, color->a);
      thickLineRGBA(renderer, centerX + half_box_side, centerY - half_box_side, centerX - half_box_side,
                    centerY + half_box_side, 10, color->r, color->g, color->b, color->a);
  }

  void Game::display_circle(SDL_Renderer *renderer, int line, int column, const SDL_Color *color)
  {
    const float centerX = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 + line * CELL_HEIGHT;

    filledCircleRGBA(renderer, centerX, centerY, half_box_side + 5, color->r, color->g, color->b, color->a);
    filledCircleRGBA(renderer, centerX, centerY, half_box_side - 5, 0, 0, 0, 255);
  }

  void Game::display_board(SDL_Renderer *renderer, const SDL_Color *player_x_color, const SDL_Color *player_o_color)
  {
    board_t grid = board.get_board();
      for (int i = 0; i < BOARD_SIZE; ++i)
      {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
          if (grid[i][j] == cross)
            display_cross(renderer, i, j, player_x_color);
          if (grid[i][j] == circle)
            display_circle(renderer, i, j, player_o_color);
        }
      }
  }

  void Game::running_state(SDL_Renderer *renderer)
  {
    display_grid(renderer, &GRID_COLOR);
    display_board(renderer, &PLAYER_X_COLOR, &PLAYER_O_COLOR);
  }

  void Game::gameover_state(SDL_Renderer *renderer, const SDL_Color *color)
  {
    display_grid(renderer, color);
    display_board(renderer, color, color);
  }

  void Game::update_game(SDL_Renderer *renderer)
  {
    switch (state)
    {
      case RUNNING_STATE:
        running_state(renderer);
        break;
      case PLAYER_X_WON_STATE:
        gameover_state(renderer, &PLAYER_X_COLOR);
        break;
      case PLAYER_O_WON_STATE:
        gameover_state(renderer, &PLAYER_O_COLOR);
        break;
      case TIE_STATE:
        gameover_state(renderer, &TIE_COLOR);
      default : {}
    }
  }
