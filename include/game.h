#ifndef GAME_H_
#define GAME_H_

using namespace std;

#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>

#define BOARD_SIZE 3
#define SCREEN_WIDTH 640.0
#define SCREEN_HEIGHT 480.0
#define CELL_WIDTH (SCREEN_WIDTH / BOARD_SIZE)
#define CELL_HEIGHT (SCREEN_HEIGHT / BOARD_SIZE)

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_0 2

#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4

#define INIT_ERROR 1
#define WINDOW_ERROR 2
#define RENDERER_ERROR 3

enum symbol_t { cross, circle, empty};
typedef array<array<symbol_t, BOARD_SIZE>, BOARD_SIZE> board_t;

void sdl_print_error(int errorNum);
void run_game(SDL_Renderer *renderer);

class Board
{
private:
  board_t board;
public:
  Board();
  void init();
  board_t get_board();;
  bool count_cells(symbol_t cell);
  void click_on_board(int line, int column, symbol_t symbol);
};

class Game
{
private:
  Board& board;
  int state;
  int playerTurn;
  const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255, .a = 255};
  const SDL_Color PLAYER_X_COLOR = { .r = 255, .g = 50, .b = 50, .a = 255};
  const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .b = 255, .a = 255};
  const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .b = 100, .a = 255};
  const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;

public:
  Game(Board& board);
  void init(Board& board);
  int get_state();
  void set_state(int newState);
  bool check_player_won(symbol_t symbol);
  void update_state(Board board);
  symbol_t get_symbol();
  void switch_player();
  void display_grid(SDL_Renderer *renderer, const SDL_Color *color);
  void display_cross(SDL_Renderer *renderer, int row, int column, const SDL_Color *color);
  void display_circle(SDL_Renderer *renderer, int row, int column, const SDL_Color *color);
  void display_board(SDL_Renderer *renderer, const SDL_Color *player_x_color, const SDL_Color *player_o_color);
  void running_state(SDL_Renderer *renderer);
  void gameover_state(SDL_Renderer *renderer, const SDL_Color *color);
  void update_game(SDL_Renderer *renderer);
};

#endif // GAME_H_
