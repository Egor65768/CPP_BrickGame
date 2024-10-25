#include "frontend.h"

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

void doDrawing_tetris(Parametrs parametr) {
  clear();
  for (int j = 0; j < FIELD_HEIGHT; j++) {
    for (int i = 0; i < FIELD_WIGTH; i++) {
      paint_pole(i, j, parametr);
    }
  }
  refresh();
}

void paint_pole(int i, int j, Parametrs parametr) {
  int fcolor;
  if (parametr.pole[i][j].block == kBlockI) {
    fcolor = kRed;
  } else if (parametr.pole[i][j].block == kBlockJ) {
    fcolor = kOrange;
  } else if (parametr.pole[i][j].block == kBlockL) {
    fcolor = kYellow;
  } else if (parametr.pole[i][j].block == kBlockO) {
    fcolor = kPink;
  } else if (parametr.pole[i][j].block == kBlockS) {
    fcolor = kGreen;
  } else if (parametr.pole[i][j].block == kBlockT) {
    fcolor = kBlue;
  } else if (parametr.pole[i][j].block == kBlockZ) {
    fcolor = kViolet;
  } else if (parametr.pole[i][j].block == kBlockRes) {
    fcolor = kGray;
  } else {
    fcolor = kWhite;
  }

  attron(COLOR_PAIR(fcolor));
  mvaddch(j, i, ' ');
  attroff(COLOR_PAIR(fcolor));
}

void TetrisLoop(Parametrs *p_parameters) {
  UserAction_t signal = Start;
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
  tetris_controller(signal, p_parameters);
  signal = Skip;
  while (p_parameters->inGame) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    doDrawing_tetris(*p_parameters);
    paint_next_fig(*p_parameters);
    int ch = getch();
    flushinp();
    signal = get_signal(ch);
    check_fast(p_parameters, signal);
    tetris_controller(signal, p_parameters);
    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    if (!p_parameters->inFast) {
      if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
          (ts2.tv_nsec =
               FALL_DELAY_NANOS - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
        nanosleep(&ts2, &ts1);
      }
    } else {
      if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
          (ts2.tv_nsec = NANOS_PER_TICK - (sp_end.tv_nsec - sp_start.tv_nsec)) >
              0) {
        nanosleep(&ts2, &ts1);
      }
    }
  }
}

void check_fast(Parametrs *paramet, UserAction_t signal1) {
  if (signal1 != paramet->dir) {
    paramet->inFast = false;
    paramet->numFast = 0;
  } else if (!paramet->inFast && signal1 == Down) {
    paramet->numFast += 1;
    if (paramet->numFast >= 2) {
      paramet->inFast = true;
    }
  }
}

void paint_next_fig(Parametrs parametr) {
  int x1, y1;
  int x = 15;
  int y = 6;
  mvprintw(0, 11, "Game: Tetris");
  mvprintw(1, 11, "Current account: %d", parametr.size_snake);
  mvprintw(2, 11, "Record: %d", parametr.record);
  mvprintw(3, 11, "Next figura:");
  attron(COLOR_PAIR(kNextfig));
  for (int i = 0; i < 4; i++) {
    x1 = x + figures[parametr.next_fig.block][parametr.next_fig.dir][i][0];
    y1 = y + figures[parametr.next_fig.block][parametr.next_fig.dir][i][1];
    mvaddch(y1, x1, ' ');
  }
  attroff(COLOR_PAIR(kNextfig));
}

UserAction_t get_signal(int ch) {
  UserAction_t signal = Skip;
  if (ch == 'a') {
    signal = Left;
  } else if (ch == 'd') {
    signal = Right;
  } else if (ch == PAUSE_KEY) {
    signal = Pause;
  } else if (ch == ACTION_KEY) {
    signal = Action;
  } else if (ch == 's') {
    signal = Down;
  } else if (ch == 'w') {
    signal = Up;
  }
  return signal;
}

void HandleTetrisLoop() {
  Parametrs parametr;
  set_defolt_parametr(&parametr);
  PrintBegin();
  TetrisLoop(&parametr);
  PrintEnd(parametr);
}

void set_defolt_parametr(Parametrs *parametr) {
  parametr->inGame = false;
  parametr->inFast = false;
  parametr->inPause = false;
  parametr->numFast = 0;
  parametr->level = 1;
  parametr->record = 0;
  parametr->next_fig.block = kBlockL;
  parametr->next_fig.dir = kDirectionFirst;
}

int CreateMenu(const char *options[], int size) {
  int highlight = 0;
  int choice = -1;
  int key;

  while (1) {
    clear();

    for (int i = 0; i < size; i++) {
      if (i == highlight) {
        attron(A_REVERSE);
      }
      mvprintw(i + 1, 1, "%s", options[i]);
      attroff(A_REVERSE);
    }
    key = getch();
    switch (key) {
      case KEY_UP:
        highlight = (highlight - 1 + size) % size;
        break;
      case KEY_DOWN:
        highlight = (highlight + 1) % size;
        break;
      case 10:
        choice = highlight;
        break;
    }
    if (choice != -1) {
      break;
    }
  }
  return choice;
}

void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i_2 = top_y + 1; i_2 < bottom_y; i_2++) {
    MVADDCH(i_2, left_x, ACS_VLINE);
    MVADDCH(i_2, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void PrintBegin() {
  int key;
  clear();
  PrintRectangle(0, BOARDS_BEGIN + BOARD_HEIGHT - 1, 0,
                 BOARDS_BEGIN + BOARD_WIDTH + HUD_WIDTH + 1);
  mvprintw(11, 6, "Press Enter to play");
  mvprintw(13, 6, "Press Esc to choose");
  mvprintw(14, 10, "another game");
  refresh();
  while (1) {
    key = getch();
    if (key == ENTER_KEY) {
      return;
    }
  }
}

void PrintEnd(Parametrs parametr) {
  int key;
  clear();
  PrintRectangle(0, BOARDS_BEGIN + BOARD_HEIGHT - 1, 0,
                 BOARDS_BEGIN + BOARD_WIDTH + HUD_WIDTH + 1);
  if (parametr.size_snake == 200) {
    mvprintw(10, 6, "YOU WIN!!!");
  }
  mvprintw(11, 6, "Press Enter");
  mvprintw(12, 6, "You account: %d", parametr.size_snake);
  mvprintw(13, 6, "Record: %d", parametr.record);
  refresh();
  while (1) {
    key = getch();
    if (key == ENTER_KEY) {
      return;
    }
  }
}

void init_color() {
  init_pair(kRed, COLOR_RED, COLOR_RED);
  init_pair(kYellow, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(kGreen, COLOR_GREEN, COLOR_GREEN);
  init_pair(kWhite, COLOR_WHITE, COLOR_WHITE);
  init_pair(kBlue, COLOR_BLUE, COLOR_BLUE);
  init_pair(kOrange, COLOR_RED, COLOR_YELLOW);
  init_pair(kPink, COLOR_RED, COLOR_BLUE);
  init_pair(kViolet, COLOR_BLUE, COLOR_RED);
  init_pair(kGray, COLOR_BLACK, COLOR_BLACK);
  init_pair(kNextfig, COLOR_MAGENTA, COLOR_MAGENTA);
}

void HandleSnakeLoop() {
  Parametrs parametr;
  set_defolt_parametr(&parametr);
  PrintBegin();
  SnakeLoop(&parametr);
  parametr.size_snake -= 4;
  PrintEnd(parametr);
}

void doDrawing_snake(Parametrs *parametr) {
  clear();
  attron(COLOR_PAIR(kWhite));
  for (int i = 0; i < FIELD_WIGTH; i++) {
    for (int j = 0; j < FIELD_HEIGHT; j++) {
      mvaddch(j, i, ' ');
    }
  }
  attroff(COLOR_PAIR(kWhite));
  attron(COLOR_PAIR(kNextfig));
  mvaddch(parametr->apple.y_p, parametr->apple.x_p, ' ');
  attroff(COLOR_PAIR(kNextfig));
  attron(COLOR_PAIR(kGreen));
  for (int i = 1; i < parametr->size_snake; i++) {
    mvaddch(parametr->snake_arr[i].y_p, parametr->snake_arr[i].x_p, ' ');
  }
  attroff(COLOR_PAIR(kGreen));
  attron(COLOR_PAIR(kBlue));
  mvaddch(parametr->snake_arr[0].y_p, parametr->snake_arr[0].x_p, ' ');
  attroff(COLOR_PAIR(kBlue));
}

void paint_snake_tablo(const Parametrs *parametr) {
  mvprintw(0, 11, "Game: Snake");
  mvprintw(1, 11, "Current level: %d", parametr->level);
  mvprintw(2, 11, "Current account: %d", parametr->size_snake - 4);
  mvprintw(3, 11, "Record: %d", parametr->record);
}

void SnakeLoop(Parametrs *p_parameters) {
  UserAction_t signal = Start;
  int level_in_game = 0;
  int sec_kol = FALL_DELAY_NANOS - level_in_game * FALL_DELAY_DECREMENT;
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
  snake_controller(signal, p_parameters);
  signal = Skip;
  while (p_parameters->inGame && p_parameters->size_snake != MAX_SIZE_SNAKE) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    int ch = getch();
    flushinp();
    signal = get_signal(ch);
    if (signal == Down) {
      signal = Up;
    } else if (signal == Up) {
      signal = Down;
    }
    doDrawing_snake(p_parameters);
    paint_snake_tablo(p_parameters);
    refresh();
    snake_controller(signal, p_parameters);
    if (p_parameters->inFast) {
      level_in_game = 10;
    } else {
      level_in_game = p_parameters->level;
    }
    sec_kol = FALL_DELAY_NANOS - level_in_game * INITIAL_FALL_DELAY;
    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec = sec_kol - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
      nanosleep(&ts2, &ts1);
    }
  }
}

int main(void) {
  WIN_INIT(50);
  setlocale(LC_ALL, "");
  srand(time(NULL));
  init_color();
  GameState state = kGameStateNone;
  const char *options[] = {"Tetris", "Snake", "Exit"};
  int size = sizeof(options) / sizeof(options[0]);
  int choice;
  while (state != kGameStateExit) {
    choice = CreateMenu(options, size);
    if (choice == 0) {
      state = kGameStateTetris;
    } else if (choice == 1) {
      state = kGameStateSnake;
    } else {
      state = kGameStateExit;
    }

    if (state == kGameStateTetris) {
      HandleTetrisLoop();
    } else if (state == kGameStateSnake) {
      HandleSnakeLoop();
    }
  }
  endwin();
  return 0;
}