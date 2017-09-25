#ifndef GAME_H_
#define GAME_H_

using namespace std;

#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>
#include <climits>
#include <chrono>
#include <thread>
#include <ctime>

#define BOARD_SIZE 5
#define PAWNS_TO_WIN 3
#define AI_EASY BOARD_SIZE / BOARD_SIZE
#define AI_MEDIUM BOARD_SIZE
#define AI_HARD BOARD_SIZE * BOARD_SIZE
#define SCREEN_WIDTH 640.0
#define SCREEN_HEIGHT 480.0
#define CELL_WIDTH (SCREEN_WIDTH / BOARD_SIZE)
#define CELL_HEIGHT (SCREEN_HEIGHT / BOARD_SIZE)

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2

#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4

#define INIT_ERROR 1
#define WINDOW_ERROR 2
#define RENDERER_ERROR 3

#define GRID_COLOR 0
#define PLAYER_X_COLOR 1
#define PLAYER_O_COLOR 2
#define TIE_COLOR 3

enum symbol_t { empty, cross, circle};
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
  board_t get_board();
  void set_case(int i, int j, symbol_t symbol);
  bool count_cells(symbol_t cell);
  void click_on_board(int line, int column, symbol_t symbol);
};


class Color
{
private:
  const SDL_Color black = { .r = 255, .g = 255, .b = 255, .a = 255};
  const SDL_Color red = { .r = 255, .g = 50, .b = 50, .a = 255};
  const SDL_Color blue = { .r = 50, .g = 100, .b = 255, .a = 255};
  const SDL_Color grey = { .r = 100, .g = 100, .b = 100, .a = 255};
public:
  const SDL_Color get_color(int color);
};

class Display
{
private:
  Color& color;
  const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
public:
  Display(Color& color);
  void grid(SDL_Renderer *renderer, const SDL_Color& color);
  void p_cross(SDL_Renderer *renderer, int line, int column, const SDL_Color& color);
  void p_circle(SDL_Renderer *renderer, int line, int column, const SDL_Color& color);
  void overgame(SDL_Renderer *renderer, Board board, const SDL_Color& col);
  void playinggame(SDL_Renderer *renderer, Board board);
};

class Game
{
private:
  Board& board;
  Display *display;
  Color color;
  int state;
  int playerTurn;

public:
  Game(Board& board);
  void init(Board& board);
  int get_state();
  int get_player_turn();
  symbol_t get_winner();
  void set_state(int newState);
  bool check_player_won(symbol_t symbol);
  void update_state(Board board);
  symbol_t get_symbol();
  void switch_player();
  void play_move(Board& board, int i, int j);
  void cancel_move(Board& board, int i, int j);
  void update_game(SDL_Renderer *renderer);
};
class Ai
{
private:
  const int maxEval = INT_MAX;
  const int minEval = INT_MIN;
  symbol_t currentPlayer;

public:
//  IA();
  void play(Game& game, Board& board, int depth);
  int calc_min(Game& game, Board& board, int depth);
  int calc_max(Game& game, Board& board, int depth);
  int score_pawns(int pawns, int player);
  int eval(Game& game, Board &board);
  int count_pawns(Board &board);
};

#endif
