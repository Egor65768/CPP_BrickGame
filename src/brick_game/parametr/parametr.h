#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_PARAMETR_PARAMETR_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_PARAMETR_PARAMETR_H

#include <stdbool.h>

#define BOARD_HEIGHT (20)
#define BOARD_WIDTH (10)

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Skip
} UserAction_t;

typedef enum {
  kBlockI = 0,
  kBlockJ = 1,
  kBlockL = 2,
  kBlockO = 3,
  kBlockS = 4,
  kBlockT = 5,
  kBlockZ = 6,
  kBlockPredict = 7,
  kBlockRes = 8,
} BlockType;

typedef enum {
  kDirectionFirst,
  kDirectionSecond,
  kDirectionThird,
  kDirectionForth,
} Direction;

typedef struct my_snake {
  int x_p;
  int y_p;
} My_snake;

typedef struct CELL {
  BlockType block;
} Cell;

typedef struct FIGURA {
  BlockType block;
  Direction dir;
  int x_;
  int y_;
} Figura;

typedef struct parametrs {
  My_snake snake_arr[200];
  My_snake apple;
  UserAction_t dir;
  bool inGame;
  bool inPause;
  bool inFast;
  int numFast;
  int size_snake;
  int record;
  int level;
  Figura fig;
  Figura next_fig;
  Cell pole[BOARD_WIDTH][BOARD_HEIGHT];

} Parametrs;

#endif