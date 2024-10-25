#include "s21_tetris.h"

BlockType GetRandomBlockType() {
  BlockType block_type = (BlockType)(rand() % (kBlockZ + 1));
  return block_type;
}

Direction GetNextBlockRotation(Direction block_rotation) {
  Direction next_block_rotation = kDirectionFirst;
  if (block_rotation == kDirectionFirst) {
    next_block_rotation = kDirectionSecond;
  } else if (block_rotation == kDirectionSecond) {
    next_block_rotation = kDirectionThird;
  } else if (block_rotation == kDirectionThird) {
    next_block_rotation = kDirectionForth;
  } else if (block_rotation == kDirectionForth) {
    next_block_rotation = kDirectionFirst;
  }
  return next_block_rotation;
}

Direction GetPreviousBlockRotation(Direction block_rotation) {
  Direction previous_block_rotation = kDirectionFirst;
  if (block_rotation == kDirectionFirst) {
    previous_block_rotation = kDirectionForth;
  } else if (block_rotation == kDirectionSecond) {
    previous_block_rotation = kDirectionFirst;
  } else if (block_rotation == kDirectionThird) {
    previous_block_rotation = kDirectionSecond;
  } else if (block_rotation == kDirectionForth) {
    previous_block_rotation = kDirectionThird;
  }
  return previous_block_rotation;
}

void InitBoard(Parametrs* p_board) {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      p_board->pole[j][i].block = kBlockPredict;
    }
  }
}

int HandleBoardCompleteLines(Parametrs* p_board) {
  int complete_lines_count = 0;
  for (int row_index = BOARD_HEIGHT; row_index >= 0; --row_index) {
    for (int row_index_2 = BOARD_HEIGHT; row_index_2 >= 0; --row_index_2) {
      bool flag = CheckBoardCompleteLine(p_board, row_index);
      if (flag) {
        complete_lines_count++;
        RemoveBoardLine(p_board, row_index);
        ApplyPhysics(p_board);
      }
    }
  }
  return complete_lines_count;
}

void RemoveBoardLine(Parametrs* p_board, int line_index) {
  for (int column_index = 0; column_index < BOARD_WIDTH; ++column_index) {
    p_board->pole[column_index][line_index].block = kBlockPredict;
  }
}

bool CheckBoardCompleteLine(Parametrs* p_board, int row_index) {
  bool flag = true;
  for (int column_index = 0; column_index < BOARD_WIDTH; ++column_index) {
    if (p_board->pole[column_index][row_index].block != kBlockRes) {
      flag = false;
    }
  }
  return flag;
}

void ApplyPhysics(Parametrs* p_board) {
  for (int row_index = BOARD_HEIGHT - 1; row_index >= 0; --row_index) {
    bool empty_line_flag = true;
    for (int column_index = 0; column_index < BOARD_WIDTH && empty_line_flag;
         ++column_index) {
      if (p_board->pole[column_index][row_index].block != kBlockPredict) {
        empty_line_flag = false;
      }
    }
    if (empty_line_flag) {
      ShiftBoardDown(p_board, row_index);
    }
  }
}

void ShiftBoardDown(Parametrs* p_board, int empty_row_index) {
  for (int row_index = empty_row_index; row_index > 1; --row_index) {
    CopyBoardLine(p_board, row_index, row_index - 1);
  }
}

void CopyBoardLine(Parametrs* p_board, int index_dest, int index_src) {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
    p_board->pole[i][index_dest].block = p_board->pole[i][index_src].block;
  }
}

Figura CreateNewFigure() {
  Figura f1;
  f1.block = GetRandomBlockType();
  f1.dir = kDirectionFirst;
  f1.x_ = BOARD_WIDTH / 2 - 1;
  f1.y_ = 1;
  return f1;
}

void add_figura_to_cell(Parametrs* paramet) {
  int x = paramet->fig.x_;
  int y = paramet->fig.y_;
  int x1, y1;
  for (int i = 0; i < TETRIS_BLOCK_SIZE; i++) {
    x1 = x + figures[paramet->fig.block][paramet->fig.dir][i][0];
    y1 = y + figures[paramet->fig.block][paramet->fig.dir][i][1];
    paramet->pole[x1][y1].block = paramet->fig.block;
  }
}

bool check_move_down(Parametrs* parametr) {
  int x = parametr->fig.x_;
  int y = parametr->fig.y_;
  int x1, y1;
  bool res = true;
  for (int i = 0; i < TETRIS_BLOCK_SIZE && res; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    if (parametr->pole[x1][y1 + 1].block == kBlockRes ||
        y1 >= PLAYFIELD_HEIGHT) {
      res = false;
    }
  }
  return res;
}

void move_down(Parametrs* parametr) {
  if (check_move_down(parametr)) {
    MarkPredictedPositions(parametr, kBlockPredict, 0, 0);
    MarkPredictedPositions(parametr, parametr->fig.block, 0, 1);
    parametr->fig.y_ += 1;
  } else {
    MarkPredictedPositions(parametr, kBlockRes, 0, 0);
    parametr->fig = parametr->next_fig;
    parametr->next_fig = CreateNewFigure();
  }
}

void MarkPredictedPositions(Parametrs* parametr, BlockType type, int delta_x,
                            int delta_y) {
  int x1, y1;
  int x = parametr->fig.x_;
  int y = parametr->fig.y_;
  for (int i = 0; i < TETRIS_BLOCK_SIZE; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    parametr->pole[x1 + delta_x][y1 + delta_y].block = type;
  }
}

bool check_move_left_or_right(Parametrs* parametr, int a) {
  int x = parametr->fig.x_;
  int y = parametr->fig.y_;
  int x1, y1;
  bool res = true;
  for (int i = 0; i < TETRIS_BLOCK_SIZE && res; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    if (parametr->pole[x1 + a][y1].block == kBlockRes || x1 + a < 0 ||
        x1 + a > PLAYFIELD_WIDTH) {
      res = false;
    }
  }
  return res;
}

void move_left_or_right(Parametrs* parametr, int a) {
  if (check_move_left_or_right(parametr, a)) {
    MarkPredictedPositions(parametr, kBlockPredict, 0, 0);
    MarkPredictedPositions(parametr, parametr->fig.block, a, 0);
    parametr->fig.x_ += a;
  }
}

void check_game_over(Parametrs* parametr) {
  bool res = false;
  int x = parametr->fig.x_;
  int y = parametr->fig.y_;
  int x1, y1;
  for (int i = 0; i < TETRIS_BLOCK_SIZE && !res; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    if (parametr->pole[x1][y1].block == kBlockRes) {
      res = true;
    }
  }
  if (res) {
    parametr->inGame = false;
  }
}

void rotation(Parametrs* parametr) {
  bool res = true;
  int x = parametr->fig.x_;
  int y = parametr->fig.y_;
  int x1, y1;
  for (int i = 0; i < TETRIS_BLOCK_SIZE; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    parametr->pole[x1][y1].block = kBlockPredict;
  }
  parametr->fig.dir = GetNextBlockRotation(parametr->fig.dir);
  for (int i = 0; i < TETRIS_BLOCK_SIZE && res; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    if (parametr->pole[x1][y1].block == kBlockRes || x1 < 0 ||
        x1 > PLAYFIELD_WIDTH || y1 < 0 || y1 > PLAYFIELD_HEIGHT) {
      res = false;
    }
  }
  if (!res) {
    parametr->fig.dir = GetPreviousBlockRotation(parametr->fig.dir);
  }
  for (int i = 0; i < TETRIS_BLOCK_SIZE; i++) {
    x1 = x + figures[parametr->fig.block][parametr->fig.dir][i][0];
    y1 = y + figures[parametr->fig.block][parametr->fig.dir][i][1];
    parametr->pole[x1][y1].block = parametr->fig.block;
  }
}

void check_pause(Parametrs* paramet, UserAction_t signal) {
  if (signal == Pause && paramet->inPause == true) {
    paramet->inPause = false;
  } else if (signal == Pause && paramet->inPause == false) {
    paramet->inPause = true;
  }
}

void result(Parametrs* paramet) {
  int num_str = HandleBoardCompleteLines(paramet);
  if (num_str == 1) {
    num_str = 100;
  } else if (num_str == 2) {
    num_str = 300;
  } else if (num_str == 3) {
    num_str = 700;
  } else if (num_str == 4) {
    num_str = 1500;
  } else {
    num_str = 0;
  }
  paramet->size_snake += num_str;
}

void file_record(Parametrs* paramet) {
  FILE* file = fopen(".record_tetris.txt", "r");
  int record;

  if (file != NULL) {
    if (fscanf(file, "%d", &record) == 1) {
      paramet->record = record;
      fclose(file);
    } else {
      fclose(file);
      file = fopen(".record_tetris.txt", "w");
      if (file != NULL) {
        fprintf(file, "%d", 0);
        fclose(file);
      }
      return;
    }

    if (record < paramet->size_snake) {
      file = fopen(".record_tetris.txt", "w");
      if (file != NULL) {
        fprintf(file, "%d", paramet->size_snake);
        fclose(file);
      }
      paramet->record = paramet->size_snake;
    }
  } else {
    file = fopen(".record_tetris.txt", "w");
    if (file != NULL) {
      fprintf(file, "%d", 0);
      fclose(file);
    }
  }
}

void setParametrs_tetris(Parametrs* paramet, UserAction_t signal) {
  check_pause(paramet, signal);
  if (!paramet->inPause) {
    srand((unsigned int)time(NULL));
    if (signal == Start) {
      InitBoard(paramet);
      paramet->inGame = true;
      paramet->size_snake = 0;
      paramet->fig = CreateNewFigure();
      paramet->next_fig = CreateNewFigure();
      add_figura_to_cell(paramet);
    } else if (signal == Left) {
      move_left_or_right(paramet, -1);
    } else if (signal == Right) {
      move_left_or_right(paramet, 1);
    } else if (signal == Action) {
      rotation(paramet);
    }
    check_game_over(paramet);
    if (signal != Action) {
      move_down(paramet);
    }
    result(paramet);
    file_record(paramet);
  }
  paramet->dir = signal;
}