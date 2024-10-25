#ifndef CPP3_BRICK_GAME_V_2_0_1_GUI_CLI_FRONTEND_H
#define CPP3_BRICK_GAME_V_2_0_1_GUI_CLI_FRONTEND_H

#include "../../brick_game/controller/s21_controller.h"
#include "../../brick_game/controller/s21_tetris_controller.h"
#include "../../brick_game/parametr/parametr.h"
#include "../../brick_game/tetris/s21_tetris.h"

#define BOARDS_BEGIN (2)
#define BOARD_HEIGHT (20)
#define HUD_WIDTH (12)
#define FIELD_HEIGHT (20)
#define FIELD_WIGTH (10)
#define ENTER_KEY (10)
#define PAUSE_KEY ('p')
#define ACTION_KEY ('q')
#define FALL_DELAY_NANOS 330000000
#define NANOS_PER_TICK 33000000
#define MAX_SIZE_SNAKE 200
#define FALL_DELAY_DECREMENT 40000000
#define INITIAL_FALL_DELAY 20000000

#define WIN_INIT(time)     \
  {                        \
    initscr();             \
    noecho();              \
    curs_set(0);           \
    keypad(stdscr, TRUE);  \
    timeout(time);         \
    nodelay(stdscr, TRUE); \
    start_color();         \
  }

#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

typedef enum {
  kGameStateNone = 0,
  kGameStateStart = 1,
  kGameStateTetris = 2,
  kGameStateSnake = 3,
  kGameStateExit = 4,
} GameState;

typedef enum {
  kRed = 0,
  kYellow = 1,
  kGreen = 2,
  kWhite = 3,
  kOrange = 4,
  kBlue = 5,
  kPink = 6,
  kViolet = 7,
  kGray = 8,
  kNextfig = 9,

} ColorGame;

// Главная функция тетриса
void HandleTetrisLoop();

// Функция отрисовки начального экрана
void PrintBegin();

// Функция создает текстовое меню
int CreateMenu(const char *options[], int size);

// Функция отрисовывает прямоугольник для начала и конца
void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x);

// Функция управления игровым процессом тетриса
void TetrisLoop(Parametrs *p_parameters);

// Функция инициализации цветов
void init_color();

// Функция отвечает за обновление и отрисовку игрового поля
void doDrawing_tetris(Parametrs parametr);

// Функция отвечает за отрисовку отдельной ячейки игрового поля
void paint_pole(int i, int j, Parametrs parametr);

// Функция обробатывает нажатия на клавиатуре
UserAction_t get_signal(int ch);

// Функция отображения информации о текущей игре
void paint_next_fig(Parametrs parametr);

// Функция проверки ускоренного падения фигуры
void check_fast(Parametrs *paramet, UserAction_t signal1);

// Функция отрисовки конечного экрана
void PrintEnd(Parametrs parametr);

// Функция устанавливает параметры по умолчанию
void set_defolt_parametr(Parametrs *parametr);

// // Главная функция змейки
void HandleSnakeLoop();

// Функция управления игровым процессом змейки
void SnakeLoop(Parametrs *p_parameters);

// Функция отрисовки змейки
void doDrawing_snake(Parametrs *parametr);

// Функция отрисовки информации о игре змейки
void paint_snake_tablo(const Parametrs *parametr);

#endif  // CPP3_BRICK_GAME_V_2_0_1_GUI_CLI_FRONTEND_H_